#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace tl::runtime {

using IndexVar = std::string;
using IndexValue = int64_t;

class IndexDomainRegistry {
public:
  // Register domain size for an index variable: domain is [0, size)
  void set_domain_size(const IndexVar& var, int64_t size) {
    if (size < 0) {
      throw std::runtime_error("Domain size must be non-negative");
    }
    domain_sizes_[var] = size;
  }

  // Get domain size
  int64_t domain_size(const IndexVar& var) const {
    auto it = domain_sizes_.find(var);
    if (it == domain_sizes_.end()) {
      throw std::runtime_error("Unknown index var: " + var);
    }
    return it->second;
  }

  // Enumerate domain values deterministically: 0..size-1
  std::vector<IndexValue> enumerate(const IndexVar& var) const {
    int64_t n = domain_size(var);
    std::vector<IndexValue> v;
    v.reserve(static_cast<size_t>(n));
    for (int64_t i = 0; i < n; ++i) {
      v.push_back(i);
    }
    return v;
  }

  // Normalize index variable list: lexicographic order + deduplication
  static std::vector<IndexVar> sort_lex(std::vector<IndexVar> vars) {
    std::sort(vars.begin(), vars.end());
    vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
    return vars;
  }

private:
  std::unordered_map<IndexVar, int64_t> domain_sizes_;
};

} // namespace tl::runtime
