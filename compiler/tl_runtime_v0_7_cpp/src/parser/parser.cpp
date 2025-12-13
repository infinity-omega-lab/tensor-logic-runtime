#include "tl/parser/parser.hpp"

#include <stdexcept>
#include <map>

namespace tl::parser {

Parser::Parser(const std::string& source) : lexer_(source) {
    current_ = lexer_.next();
    if (current_.type == TokenType::EndOfFile) {
        end_ = true;
    }
}

std::unique_ptr<ast::Program> Parser::parse_program() {
    auto program = std::make_unique<ast::Program>();
    while (!end_) {
        auto stmt = parse_statement();
        if (stmt) {
            program->statements.push_back(std::move(stmt));
        }
        if (current_.type == TokenType::EndOfFile) {
            end_ = true;
        }
    }
    return program;
}

Token Parser::consume(TokenType type, const std::string& context) {
    if (current_.type != type) {
        throw std::runtime_error("Unexpected token in " + context + " at line " +
                                 std::to_string(current_.line));
    }
    Token t = current_;
    current_ = lexer_.next();
    return t;
}

bool Parser::match(TokenType type) {
    if (current_.type == type) {
        current_ = lexer_.next();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) {
    return current_.type == type;
}

Token Parser::advance() {
    Token t = current_;
    current_ = lexer_.next();
    if (current_.type == TokenType::EndOfFile) {
        end_ = true;
    }
    return t;
}

std::unique_ptr<ast::Statement> Parser::parse_statement() {
    switch (current_.type) {
        case TokenType::Comment:
            return parse_comment();
        case TokenType::Pragma:
            return parse_pragma();
        case TokenType::Identifier: {
            // Could be assign/accumulate or function-like statement.
            // Look ahead by parsing lhs then deciding.
            return parse_assign_or_accumulate();
        }
        case TokenType::EndOfFile:
            return nullptr;
        default:
            throw std::runtime_error("Unexpected start of statement at line " +
                                     std::to_string(current_.line));
    }
}

std::unique_ptr<ast::Statement> Parser::parse_comment() {
    auto text = current_.lexeme;
    advance();
    auto stmt = std::make_unique<ast::CommentStmt>();
    stmt->text = std::move(text);
    return stmt;
}

std::unique_ptr<ast::Statement> Parser::parse_pragma() {
    advance();  // consume #pragma

    std::string name;
    std::map<std::string, std::string> fields;

    if (current_.type == TokenType::Identifier) {
        name = advance().lexeme;
    }

    if (current_.type == TokenType::LBrace) {
        advance();  // '{'
        fields = parse_pragma_fields();
        consume(TokenType::RBrace, "pragma body end");
    }

    auto stmt = std::make_unique<ast::PragmaStmt>();
    stmt->name = std::move(name);
    stmt->fields = std::move(fields);
    return stmt;
}

std::map<std::string, std::string> Parser::parse_pragma_fields() {
    std::map<std::string, std::string> fields;
    if (check(TokenType::RBrace)) {
        return fields;
    }
    while (true) {
        Token key = consume(TokenType::Identifier, "pragma field key");
        consume(TokenType::Colon, "pragma field colon");
        Token value = consume(TokenType::StringLiteral, "pragma field value");
        fields[key.lexeme] = value.lexeme;
        if (match(TokenType::Comma)) {
            continue;
        }
        break;
    }
    return fields;
}

std::unique_ptr<ast::Statement> Parser::parse_assign_or_accumulate() {
    Token id = consume(TokenType::Identifier, "statement head");

    // Function-call statement without indices.
    if (current_.type == TokenType::LParen) {
        auto call_expr = std::make_unique<ast::FunctionCall>();
        call_expr->callee = id.lexeme;
        advance();  // '('
        call_expr->args = parse_arg_list();
        consume(TokenType::RParen, "function call ')'");

        auto stmt = std::make_unique<ast::FunctionCallStmt>();
        stmt->call = std::move(*call_expr);
        return stmt;
    }

    std::vector<ast::Index> indices;
    if (current_.type == TokenType::LBracket) {
        advance();
        indices = parse_index_list();
        consume(TokenType::RBracket, "index list ']'");
    }

    // Aggregator-call statement: id[indexes](args)
    if (!indices.empty() && current_.type == TokenType::LParen) {
        advance();  // '('
        auto args = parse_arg_list();
        consume(TokenType::RParen, "aggregator call ')'");
        auto stmt = std::make_unique<ast::AggregatorCallStmt>();
        stmt->call.callee = id.lexeme;
        stmt->call.indices = std::move(indices);
        stmt->call.args = std::move(args);
        return stmt;
    }

    // Tensor reference LHS for assign/accumulate
    ast::TensorRef lhs;
    lhs.name = id.lexeme;
    lhs.indices = std::move(indices);

    if (current_.type == TokenType::Assign ||
    current_.type == TokenType::PlusAssign) {

    ast::AssignKind kind = ast::AssignKind::Assign;
    if (current_.type == TokenType::PlusAssign) {
        kind = ast::AssignKind::PlusAssign;
    }

    advance();
    auto rhs = parse_expr();

    auto stmt = std::make_unique<ast::AssignStmt>();
    stmt->lhs = std::move(lhs);
    stmt->kind = kind;
    stmt->rhs = std::move(rhs);
    return stmt;
}

if (current_.type == TokenType::MaxAssign ||
    current_.type == TokenType::AvgAssign) {

    ast::AccumulateKind kind = ast::AccumulateKind::Add;
    if (current_.type == TokenType::MaxAssign) {
        kind = ast::AccumulateKind::Max;
    } else if (current_.type == TokenType::AvgAssign) {
        kind = ast::AccumulateKind::Avg;
    }

    advance();
    auto rhs = parse_expr();

    auto stmt = std::make_unique<ast::AccumulateStmt>();
    stmt->lhs = std::move(lhs);
    stmt->kind = kind;
    stmt->rhs = std::move(rhs);
    return stmt;
}

    throw std::runtime_error("Expected assignment, accumulate, or call after identifier at line " +
                             std::to_string(current_.line));
}

ast::TensorRef Parser::parse_tensor_ref() {
    Token name_tok = consume(TokenType::Identifier, "tensor ref");
    ast::TensorRef ref;
    ref.name = name_tok.lexeme;
    if (match(TokenType::LBracket)) {
        ref.indices = parse_index_list();
        consume(TokenType::RBracket, "tensor ref closing bracket");
    }
    return ref;
}

std::vector<ast::Index> Parser::parse_index_list() {
    std::vector<ast::Index> indices;
    indices.push_back(parse_index());
    while (match(TokenType::Comma)) {
        indices.push_back(parse_index());
    }
    return indices;
}

ast::Index Parser::parse_index() {
    if (match(TokenType::Star)) {
        Token id = consume(TokenType::Identifier, "star index identifier");
        ast::Index idx;
        idx.kind = ast::Index::Kind::StarId;
        idx.name = id.lexeme;
        return idx;
    }
    if (current_.type == TokenType::Identifier) {
        Token id = advance();
        ast::Index idx;
        idx.kind = ast::Index::Kind::Id;
        idx.name = id.lexeme;
        return idx;
    }
    if (current_.type == TokenType::Number) {
        Token num = advance();
        ast::Index idx;
        idx.kind = ast::Index::Kind::Number;
        idx.number = std::stod(num.lexeme);
        return idx;
    }
    throw std::runtime_error("Invalid index at line " + std::to_string(current_.line));
}

std::unique_ptr<ast::Expression> Parser::parse_expr() {
    // expr ::= sum_expr | product_expr | function_call | aggregator_call | number
    // sum_expr already nests product_expr, so treat expr as sum_expr entry point.
    return parse_sum_expr();
}

std::unique_ptr<ast::Expression> Parser::parse_sum_expr() {
    auto left = parse_product_expr();
    while (current_.type == TokenType::Plus) {
        advance();
        auto right = parse_product_expr();
        auto bin = std::make_unique<ast::BinaryExpr>();
        bin->op = ast::BinaryOpKind::Add;
        bin->left = std::move(left);
        bin->right = std::move(right);
        left = std::move(bin);
    }
    return left;
}

std::unique_ptr<ast::Expression> Parser::parse_product_expr() {
    auto left = parse_term();
    while (current_.type == TokenType::Identifier || current_.type == TokenType::Number ||
           current_.type == TokenType::LParen) {
        // Implicit multiplication (Einstein summation style) as consecutive terms.
        auto right = parse_term();
        auto bin = std::make_unique<ast::BinaryExpr>();
        bin->op = ast::BinaryOpKind::Multiply;
        bin->left = std::move(left);
        bin->right = std::move(right);
        left = std::move(bin);
    }
    return left;
}

std::unique_ptr<ast::Expression> Parser::parse_term() {
    if (current_.type == TokenType::Number) {
        Token num = advance();
        auto lit = std::make_unique<ast::NumberLiteral>();
        lit->value = std::stod(num.lexeme);
        return lit;
    }
    if (current_.type == TokenType::Identifier) {
        // Could be tensor_ref, function_call, or aggregator_call
        // Look ahead for '(' => function/aggregator, '[' + '(' => aggregator
        Token id = advance();
        if (current_.type == TokenType::LBracket) {
            // aggregator_call ::= id "[" index_list "]" "(" arg_list ")"
            // If '(' follows bracket block, aggregator_call; else tensor_ref.
            std::vector<ast::Index> indices;
            advance();  // consume '['
            indices = parse_index_list();
            consume(TokenType::RBracket, "aggregator/tensor closing bracket");
            if (current_.type == TokenType::LParen) {
                auto call = std::make_unique<ast::AggregatorCall>();
                call->callee = id.lexeme;
                call->indices = std::move(indices);
                advance();  // '('
                call->args = parse_arg_list();
                consume(TokenType::RParen, "aggregator call ')'");
                return call;
            }
            auto tref = std::make_unique<ast::TensorRef>();
            tref->name = id.lexeme;
            tref->indices = std::move(indices);
            return tref;
        }
        if (current_.type == TokenType::LParen) {
            auto call = std::make_unique<ast::FunctionCall>();
            call->callee = id.lexeme;
            advance();  // '('
            call->args = parse_arg_list();
            consume(TokenType::RParen, "function call ')'");
            return call;
        }
        auto ident = std::make_unique<ast::TensorRef>();
        ident->name = id.lexeme;
        return ident;
    }
    if (current_.type == TokenType::LParen) {
        advance();
        auto expr = parse_expr();
        consume(TokenType::RParen, "grouped expression");
        return expr;
    }
    throw std::runtime_error("Unexpected term at line " + std::to_string(current_.line));
}

std::unique_ptr<ast::Expression> Parser::parse_function_call() {
    Token id = consume(TokenType::Identifier, "function call");
    consume(TokenType::LParen, "function call '('");
    auto args = parse_arg_list();
    consume(TokenType::RParen, "function call ')'");

    auto call = std::make_unique<ast::FunctionCall>();
    call->callee = id.lexeme;
    call->args = std::move(args);
    return call;
}

std::unique_ptr<ast::Expression> Parser::parse_aggregator_call() {
    Token id = consume(TokenType::Identifier, "aggregator call");
    consume(TokenType::LBracket, "aggregator '['");
    auto indices = parse_index_list();
    consume(TokenType::RBracket, "aggregator ']'");
    consume(TokenType::LParen, "aggregator '('");
    auto args = parse_arg_list();
    consume(TokenType::RParen, "aggregator ')'");

    auto agg = std::make_unique<ast::AggregatorCall>();
    agg->callee = id.lexeme;
    agg->indices = std::move(indices);
    agg->args = std::move(args);
    return agg;
}

std::vector<std::unique_ptr<ast::Expression>> Parser::parse_arg_list() {
    std::vector<std::unique_ptr<ast::Expression>> args;
    if (current_.type == TokenType::RParen) {
        return args;
    }
    args.push_back(parse_expr());
    while (match(TokenType::Comma)) {
        args.push_back(parse_expr());
    }
    return args;
}

}  // namespace tl::parser
