#pragma once

#include <memory>
#include <map>
#include <string>

#include "tl/ast/nodes.hpp"
#include "tl/parser/lexer.hpp"

namespace tl::parser {

class Parser {
public:
    explicit Parser(const std::string& source);
    std::unique_ptr<ast::Program> parse_program();

private:
    Token consume(TokenType type, const std::string& context);
    bool match(TokenType type);
    bool check(TokenType type);
    Token advance();

    std::unique_ptr<ast::Statement> parse_statement();
    std::unique_ptr<ast::Statement> parse_comment();
    std::unique_ptr<ast::Statement> parse_pragma();
    std::unique_ptr<ast::Statement> parse_assign_or_accumulate();
    std::unique_ptr<ast::Statement> parse_function_or_aggregator();

    ast::TensorRef parse_tensor_ref();
    std::vector<ast::Index> parse_index_list();
    ast::Index parse_index();
    std::unique_ptr<ast::Expression> parse_expr();
    std::unique_ptr<ast::Expression> parse_sum_expr();
    std::unique_ptr<ast::Expression> parse_product_expr();
    std::unique_ptr<ast::Expression> parse_term();
    std::unique_ptr<ast::Expression> parse_function_call();
    std::unique_ptr<ast::Expression> parse_aggregator_call();
    std::vector<std::unique_ptr<ast::Expression>> parse_arg_list();

    std::map<std::string, std::string> parse_pragma_fields();

    Lexer lexer_;
    Token current_;
    bool end_{false};
};

}  // namespace tl::parser
