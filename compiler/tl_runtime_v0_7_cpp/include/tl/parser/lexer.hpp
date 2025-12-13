#pragma once

#include <string>
#include <vector>

#include "tl/parser/token.hpp"

namespace tl::parser {

class Lexer {
public:
    explicit Lexer(std::string source);

    Token next();
    const Token& peek();
    bool has_more();

private:
    char current() const;
    char advance();
    bool match(char expected);
    void skip_whitespace();
    Token make_token(TokenType type, const std::string& lexeme, std::size_t start_col);
    Token identifier_or_keyword(std::size_t start_col);
    Token number(std::size_t start_col);
    Token string_literal(std::size_t start_col);
    Token comment(std::size_t start_col);

    std::string source_;
    std::size_t index_{0};
    std::size_t line_{1};
    std::size_t column_{1};
    Token lookahead_;
    bool has_lookahead_{false};
    bool end_{false};
};

}  // namespace tl::parser
