#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace tl::ast {

struct Node {
    virtual ~Node() = default;
};

struct Expression : Node {
};

struct NumberLiteral : Expression {
    double value{};
};

struct Identifier : Expression {
    std::string name;
};

struct Index {
    enum class Kind { Id, StarId, Number };
    Kind kind{Kind::Id};
    std::string name;   // used for Id and StarId
    double number{};    // used for Number
};

struct TensorRef : Expression {
    std::string name;
    std::vector<Index> indices;
};

struct FunctionCall : Expression {
    std::string callee;
    std::vector<std::unique_ptr<Expression>> args;
};

struct AggregatorCall : Expression {
    std::string callee;
    std::vector<Index> indices;
    std::vector<std::unique_ptr<Expression>> args;
};

enum class BinaryOpKind { Add, Multiply };

struct BinaryExpr : Expression {
    BinaryOpKind op{BinaryOpKind::Add};
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
};

struct Statement : Node {
    virtual ~Statement() = default;
};

enum class AssignKind {
    Assign,     // =
    PlusAssign  // +=
};

struct AssignStmt : Statement {
    TensorRef lhs;
    AssignKind kind{AssignKind::Assign};  // ← ★これを追加
    std::unique_ptr<Expression> rhs;
};


enum class AccumulateKind { Add, Max, Avg };

struct AccumulateStmt : Statement {
    TensorRef lhs;
    AccumulateKind kind{AccumulateKind::Add};
    std::unique_ptr<Expression> rhs;
};

struct FunctionCallStmt : Statement {
    FunctionCall call;
};

struct AggregatorCallStmt : Statement {
    AggregatorCall call;
};

struct CommentStmt : Statement {
    std::string text;
};

struct PragmaStmt : Statement {
    std::string name;
    std::map<std::string, std::string> fields;
};

struct Program : Node {
    std::vector<std::unique_ptr<Statement>> statements;
};

}  // namespace tl::ast
