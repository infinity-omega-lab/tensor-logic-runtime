#include "tl/runtime/reduce_executor.hpp"

#include <algorithm>
#include <limits>
#include <stdexcept>

namespace tl::runtime {

ReduceExecutor::ReduceExecutor(IndexDomainRegistry& domains, TensorStore& store)
    : domains_(domains), store_(store) {}

void ReduceExecutor::execute(const ReducePlan& plan, const LhsTarget& lhs, EvalFn eval_rhs) {
  std::vector<IndexVar> reduce_vars = IndexDomainRegistry::sort_lex(plan.reduce_vars);
  const std::vector<IndexVar>& output_vars = plan.output_vars;

  IndexBinding binding;

  auto project_value = [&](IndexBinding& env) -> Value {
    Value acc = 0.0;
    if (plan.proj == ProjectionKind::Max) {
      acc = -std::numeric_limits<Value>::infinity();
    }

    std::size_t count = 0;
    auto traverse_reduce = [&](auto&& self, std::size_t idx) -> void {
      if (idx == reduce_vars.size()) {
        ++count;
        Value v = eval_rhs(env);
        switch (plan.proj) {
          case ProjectionKind::Sum:
          case ProjectionKind::Avg:
            acc += v;
            break;
          case ProjectionKind::Max:
            acc = std::max(acc, v);
            break;
        }
        return;
      }

      const IndexVar& var = reduce_vars[idx];
      const auto values = domains_.enumerate(var);
      auto prev = env.find(var);
      const bool had_prev = prev != env.end();
      IndexValue saved = had_prev ? prev->second : IndexValue{};
      for (IndexValue iv : values) {
        env[var] = iv;
        self(self, idx + 1);
      }
      if (had_prev) {
        env[var] = saved;
      } else {
        env.erase(var);
      }
    };

    traverse_reduce(traverse_reduce, 0);

    if (plan.proj == ProjectionKind::Avg && count > 0) {
      acc /= static_cast<Value>(count);
    }

    return acc;
  };

  auto resolve_coord = [&](const IndexBinding& env) -> Coord {
    Coord coord;
    coord.reserve(lhs.lhs_vars.size());
    for (const auto& var : lhs.lhs_vars) {
      auto it = env.find(var);
      if (it == env.end()) {
        throw std::runtime_error("Missing binding for LHS var: " + var);
      }
      coord.push_back(it->second);
    }
    return coord;
  };

  auto apply_update = [&](const Coord& coord, Value value) {
    Value current = store_.get(lhs.tensor_id, coord);
    Value result = value;
    switch (plan.update) {
      case UpdateKind::Set:
        result = value;
        break;
      case UpdateKind::Add:
        result = current + value;
        break;
      case UpdateKind::MaxSet:
        result = std::max(current, value);
        break;
      case UpdateKind::AvgSet:
        throw std::logic_error(
            "AvgSet is not supported in the v0.7.x reference interpreter");
    }
    store_.set(lhs.tensor_id, coord, result);
  };

  auto traverse_output = [&](auto&& self, std::size_t idx) -> void {
    if (idx == output_vars.size()) {
      Value projected = project_value(binding);
      Coord coord = resolve_coord(binding);
      apply_update(coord, projected);
      return;
    }

    const IndexVar& var = output_vars[idx];
    const auto values = domains_.enumerate(var);
    auto prev = binding.find(var);
    const bool had_prev = prev != binding.end();
    IndexValue saved = had_prev ? prev->second : IndexValue{};
    for (IndexValue iv : values) {
      binding[var] = iv;
      self(self, idx + 1);
    }
    if (had_prev) {
      binding[var] = saved;
    } else {
      binding.erase(var);
    }
  };

  traverse_output(traverse_output, 0);
}

}  // namespace tl::runtime
