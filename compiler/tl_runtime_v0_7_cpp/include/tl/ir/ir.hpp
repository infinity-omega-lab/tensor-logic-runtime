#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace tl::ir {

struct Index {
    enum class Kind { Id, StarId, Number };
    Kind kind{Kind::Id};
    std::string name;
    double number{};
};

struct TensorRef {
    std::string name;
    std::vector<Index> indices;
};

struct Expr;
using ExprPtr = std::shared_ptr<Expr>;

struct Expr {
    virtual ~Expr() = default;
};

struct NumberExpr : Expr {
    double value{};
};

struct TensorExpr : Expr {
    TensorRef ref;
};

enum class BinaryOp { Add, Multiply };

struct BinaryExpr : Expr {
    BinaryOp op{BinaryOp::Add};
    ExprPtr left;
    ExprPtr right;
};

struct CallExpr : Expr {
    std::string callee;
    std::vector<ExprPtr> args;
    bool is_aggregator{false};
    std::vector<Index> indices;  // only used when is_aggregator
};

struct Instruction {
    virtual ~Instruction() = default;
};

struct AssignInst : Instruction {
    TensorRef lhs;
    ExprPtr rhs;
};

enum class AccumulateOp { Add, Max, Avg };

struct AccumulateInst : Instruction {
    TensorRef lhs;
    AccumulateOp op{AccumulateOp::Add};
    ExprPtr rhs;
};

struct CallInst : Instruction {
    CallExpr call;
};

struct Program {
    std::vector<std::unique_ptr<Instruction>> instructions;
    std::map<std::string, std::string> pragmas;  // last pragma wins per key
};

}  // namespace tl::ir
