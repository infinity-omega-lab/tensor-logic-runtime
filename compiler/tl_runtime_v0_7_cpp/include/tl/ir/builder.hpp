#pragma once

#include "tl/ast/nodes.hpp"
#include "tl/ir/ir.hpp"

namespace tl::ir {

class Builder {
public:
    Program build(const ast::Program& program);

private:
    ExprPtr build_expr(const ast::Expression& expr);
    TensorRef build_tensor_ref(const ast::TensorRef& ref);
    Index build_index(const ast::Index& idx);
};

}  // namespace tl::ir
