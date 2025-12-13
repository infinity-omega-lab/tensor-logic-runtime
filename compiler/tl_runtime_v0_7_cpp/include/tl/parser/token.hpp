#pragma once

#include <string>

namespace tl::parser {

enum class TokenType {
    Identifier,
    Number,
    Plus,
    Star,
    Comma,
    LBracket,
    RBracket,
    LParen,
    RParen,
    Assign,
    PlusAssign,
    MaxAssign,
    AvgAssign,
    EndOfFile,
    Comment,
    Pragma,
    Colon,
    LBrace,
    RBrace,
    StringLiteral,
    Unknown
};

struct Token {
    TokenType type{};
    std::string lexeme;
    std::size_t line{1};
    std::size_t column{1};
};

}  // namespace tl::parser
