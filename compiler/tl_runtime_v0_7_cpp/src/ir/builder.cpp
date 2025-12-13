#include "tl/ir/builder.hpp"

#include <stdexcept>

namespace tl::ir {

Program Builder::build(const ast::Program& program) {
    Program ir_prog;
    for (const auto& stmt_ptr : program.statements) {
        if (auto assign = dynamic_cast<ast::AssignStmt*>(stmt_ptr.get())) {
            auto inst = std::make_unique<AssignInst>();
            inst->lhs = build_tensor_ref(assign->lhs);
            inst->rhs = build_expr(*assign->rhs);
            ir_prog.instructions.push_back(std::move(inst));
        } else if (auto acc = dynamic_cast<ast::AccumulateStmt*>(stmt_ptr.get())) {
            auto inst = std::make_unique<AccumulateInst>();
            inst->lhs = build_tensor_ref(acc->lhs);
            switch (acc->kind) {
                case ast::AccumulateKind::Add:
                    inst->op = AccumulateOp::Add;
                    break;
                case ast::AccumulateKind::Max:
                    inst->op = AccumulateOp::Max;
                    break;
                case ast::AccumulateKind::Avg:
                    inst->op = AccumulateOp::Avg;
                    break;
            }
            inst->rhs = build_expr(*acc->rhs);
            ir_prog.instructions.push_back(std::move(inst));
        } else if (auto fc = dynamic_cast<ast::FunctionCallStmt*>(stmt_ptr.get())) {
            auto inst = std::make_unique<CallInst>();
            CallExpr call;
            call.callee = fc->call.callee;
            call.is_aggregator = false;
            for (const auto& arg : fc->call.args) {
                call.args.push_back(build_expr(*arg));
            }
            inst->call = std::move(call);
            ir_prog.instructions.push_back(std::move(inst));
        } else if (auto ac = dynamic_cast<ast::AggregatorCallStmt*>(stmt_ptr.get())) {
            auto inst = std::make_unique<CallInst>();
            CallExpr call;
            call.callee = ac->call.callee;
            call.is_aggregator = true;
            for (const auto& idx : ac->call.indices) {
                call.indices.push_back(build_index(idx));
            }
            for (const auto& arg : ac->call.args) {
                call.args.push_back(build_expr(*arg));
            }
            inst->call = std::move(call);
            ir_prog.instructions.push_back(std::move(inst));
        } else if (auto pragma = dynamic_cast<ast::PragmaStmt*>(stmt_ptr.get())) {
            // Keep last value for a pragma key to reflect latest directive.
            for (const auto& kv : pragma->fields) {
                ir_prog.pragmas[kv.first] = kv.second;
            }
        } else if (dynamic_cast<ast::CommentStmt*>(stmt_ptr.get())) {
            // Comments are ignored in IR.
        } else {
            throw std::runtime_error("Unhandled AST statement during IR build");
        }
    }
    return ir_prog;
}

ExprPtr Builder::build_expr(const ast::Expression& expr) {
    if (auto num = dynamic_cast<const ast::NumberLiteral*>(&expr)) {
        auto node = std::make_shared<NumberExpr>();
        node->value = num->value;
        return node;
    }
    if (auto tref = dynamic_cast<const ast::TensorRef*>(&expr)) {
        auto node = std::make_shared<TensorExpr>();
        node->ref = build_tensor_ref(*tref);
        return node;
    }
    if (auto bin = dynamic_cast<const ast::BinaryExpr*>(&expr)) {
        auto node = std::make_shared<BinaryExpr>();
        node->op = (bin->op == ast::BinaryOpKind::Add) ? BinaryOp::Add : BinaryOp::Multiply;
        node->left = build_expr(*bin->left);
        node->right = build_expr(*bin->right);
        return node;
    }
    if (auto call = dynamic_cast<const ast::FunctionCall*>(&expr)) {
        auto node = std::make_shared<CallExpr>();
        node->callee = call->callee;
        node->is_aggregator = false;
        for (const auto& arg : call->args) {
            node->args.push_back(build_expr(*arg));
        }
        return node;
    }
    if (auto agg = dynamic_cast<const ast::AggregatorCall*>(&expr)) {
        auto node = std::make_shared<CallExpr>();
        node->callee = agg->callee;
        node->is_aggregator = true;
        for (const auto& idx : agg->indices) {
            node->indices.push_back(build_index(idx));
        }
        for (const auto& arg : agg->args) {
            node->args.push_back(build_expr(*arg));
        }
        return node;
    }
    throw std::runtime_error("Unhandled AST expression during IR build");
}

TensorRef Builder::build_tensor_ref(const ast::TensorRef& ref) {
    TensorRef out;
    out.name = ref.name;
    for (const auto& idx : ref.indices) {
        out.indices.push_back(build_index(idx));
    }
    return out;
}

Index Builder::build_index(const ast::Index& idx) {
    Index out;
    switch (idx.kind) {
        case ast::Index::Kind::Id:
            out.kind = Index::Kind::Id;
            out.name = idx.name;
            break;
        case ast::Index::Kind::StarId:
            out.kind = Index::Kind::StarId;
            out.name = idx.name;
            break;
        case ast::Index::Kind::Number:
            out.kind = Index::Kind::Number;
            out.number = idx.number;
            break;
    }
    return out;
}

}  // namespace tl::ir
