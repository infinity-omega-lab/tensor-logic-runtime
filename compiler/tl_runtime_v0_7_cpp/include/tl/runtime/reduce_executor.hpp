#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

#include "tl/runtime/index_domain.hpp"
#include "tl/runtime/tensor_store.hpp"

namespace tl::runtime {

using Value = double;
using IndexVar = std::string;
using IndexValue = int64_t;
using IndexBinding = std::unordered_map<IndexVar, IndexValue>;

enum class ProjectionKind { Sum, Max, Avg };
// AvgSet is retained for parser/IR completeness but is intentionally unsupported
// in the v0.7.x reference interpreter to avoid undefined or order-dependent behavior.
enum class UpdateKind { Set, Add, MaxSet, AvgSet };

struct ReducePlan {
  std::vector<IndexVar> output_vars;  // O (fixed order)
  std::vector<IndexVar> reduce_vars;  // R (normalized via sort_lex)
  ProjectionKind proj;
  UpdateKind update;
};

struct LhsTarget {
  TensorId tensor_id;
  std::vector<IndexVar> lhs_vars;  // plain indices only (no *k)
};

using EvalFn = std::function<Value(const IndexBinding&)>;

class ReduceExecutor {
public:
  ReduceExecutor(IndexDomainRegistry& domains, TensorStore& store);

  void execute(const ReducePlan& plan, const LhsTarget& lhs, EvalFn eval_rhs);

private:
  IndexDomainRegistry& domains_;
  TensorStore& store_;
};

}  // namespace tl::runtime
