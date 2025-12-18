#pragma once
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <stdexcept>

namespace tl::runtime {

using Value = double;
using TensorId = int;
using IndexValue = int64_t;
using Coord = std::vector<IndexValue>;

struct CoordHash {
  size_t operator()(const Coord& c) const {
    size_t h = 0;
    for (auto v : c) {
      h ^= std::hash<IndexValue>{}(v) + 0x9e3779b9 + (h<<6) + (h>>2);
    }
    return h;
  }
};

class TensorStore {
public:
  void register_tensor(TensorId id, const std::vector<int64_t>& shape) {
    if (tensors_.count(id)) {
      throw std::runtime_error("Tensor already registered");
    }
    tensors_[id] = Tensor{shape, {}};
  }

  Value get(TensorId id, const Coord& coord) const {
    auto it = tensors_.find(id);
    if (it == tensors_.end()) {
      throw std::runtime_error("Unknown tensor id");
    }
    auto dit = it->second.data.find(coord);
    if (dit == it->second.data.end()) {
      return 0.0;
    }
    return dit->second;
  }

  void set(TensorId id, const Coord& coord, Value v) {
    auto it = tensors_.find(id);
    if (it == tensors_.end()) {
      throw std::runtime_error("Unknown tensor id");
    }
    it->second.data[coord] = v;
  }

private:
  struct Tensor {
    std::vector<int64_t> shape;
    std::unordered_map<Coord, Value, CoordHash> data;
  };

  std::unordered_map<TensorId, Tensor> tensors_;
};

} // namespace tl::runtime
