#include <cassert>
#include <iostream>

#include "tl/runtime/reduce_executor.hpp"

int main() {
  using namespace tl::runtime;

  IndexDomainRegistry domains;
  const IndexVar k = "k";
  const int64_t N = 5;
  domains.set_domain_size(k, N);

  TensorStore store;
  const TensorId tensorA = 0;
  const TensorId tensorB = 1;
  store.register_tensor(tensorA, {});
  store.register_tensor(tensorB, {N});

  for (IndexValue i = 0; i < N; ++i) {
    store.set(tensorB, Coord{i}, static_cast<Value>(i + 1));
  }

  ReducePlan plan;
  plan.output_vars = {};
  plan.reduce_vars = {k};
  plan.proj = ProjectionKind::Sum;
  plan.update = UpdateKind::Set;

  LhsTarget lhs{tensorA, {}};
  ReduceExecutor executor(domains, store);

  EvalFn eval_rhs = [&](const IndexBinding& binding) {
    auto it = binding.find(k);
    assert(it != binding.end());
    return store.get(tensorB, Coord{it->second});
  };

  executor.execute(plan, lhs, eval_rhs);

  Value expected = 0.0;
  for (IndexValue i = 0; i < N; ++i) {
    expected += store.get(tensorB, Coord{i});
  }
  Value result = store.get(tensorA, Coord{});

  assert(result == expected);
  std::cout << "reduce_executor_deterministic_sum passed\n";
  return 0;
}
