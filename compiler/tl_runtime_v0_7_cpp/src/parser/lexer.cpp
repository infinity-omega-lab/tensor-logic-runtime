#include "tl/parser/lexer.hpp"

#include <cctype>
#include <stdexcept>

namespace tl::parser {

Lexer::Lexer(std::string source) : source_(std::move(source)) {}

bool Lexer::has_more() {
    return !end_;
}

const Token& Lexer::peek() {
    if (!has_lookahead_) {
        lookahead_ = next();
        has_lookahead_ = true;
    }
    return lookahead_;
}

Token Lexer::next() {
    if (has_lookahead_) {
        has_lookahead_ = false;
        return lookahead_;
    }

    skip_whitespace();
    if (index_ >= source_.size()) {
        end_ = true;
        return make_token(TokenType::EndOfFile, "", column_);
    }

    const char c = advance();
    const std::size_t start_col = column_ - 1;

    switch (c) {
        case '+':
            if (match('=')) return make_token(TokenType::PlusAssign, "+=", start_col);
            return make_token(TokenType::Plus, "+", start_col);
        case '*':
            return make_token(TokenType::Star, "*", start_col);
        case '=':
            return make_token(TokenType::Assign, "=", start_col);
        case ',':
            return make_token(TokenType::Comma, ",", start_col);
        case '[':
            return make_token(TokenType::LBracket, "[", start_col);
        case ']':
            return make_token(TokenType::RBracket, "]", start_col);
        case '(':
            return make_token(TokenType::LParen, "(", start_col);
        case ')':
            return make_token(TokenType::RParen, ")", start_col);
        case ':':
            return make_token(TokenType::Colon, ":", start_col);
        case '{':
            return make_token(TokenType::LBrace, "{", start_col);
        case '}':
            return make_token(TokenType::RBrace, "}", start_col);
        case '"':
            return string_literal(start_col);
       case '#':
            if (index_ + 6 <= source_.size() && source_.substr(index_, 6) == "pragma") {
                index_ += 6;
                column_ += 6;
                return make_token(TokenType::Pragma, "#pragma", start_col);
            }
            // 通常コメントは空白扱いとして捨てる
            comment(start_col);
            return next();
        default:
            if (std::isalpha(static_cast<unsigned char>(c))) {
                return identifier_or_keyword(start_col);
            }
            if (std::isdigit(static_cast<unsigned char>(c))) {
                index_--;  // step back so number() can consume this digit
                column_--;
                return number(start_col);
            }
            return make_token(TokenType::Unknown, std::string(1, c), start_col);
    }
}

char Lexer::current() const {
    if (index_ >= source_.size()) return '\0';
    return source_[index_];
}

char Lexer::advance() {
    if (index_ >= source_.size()) return '\0';
    char c = source_[index_++];
    if (c == '\n') {
        ++line_;
        column_ = 1;
    } else {
        ++column_;
    }
    return c;
}

bool Lexer::match(char expected) {
    if (index_ >= source_.size() || source_[index_] != expected) {
        return false;
    }
    advance();
    return true;
}

void Lexer::skip_whitespace() {
    while (index_ < source_.size()) {
        char c = current();
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') {
            advance();
            continue;
        }
        break;
    }
}

Token Lexer::make_token(TokenType type, const std::string& lexeme, std::size_t start_col) {
    return Token{type, lexeme, line_, start_col};
}

Token Lexer::identifier_or_keyword(std::size_t start_col) {
    std::string value;
    value.push_back(source_[index_ - 1]);
    while (index_ < source_.size()) {
        char c = current();
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
            value.push_back(c);
            advance();
        } else {
            break;
        }
    }

    if (value == "max" && match('=')) {
        return make_token(TokenType::MaxAssign, "max=", start_col);
    }
    if (value == "avg" && match('=')) {
        return make_token(TokenType::AvgAssign, "avg=", start_col);
    }

    return make_token(TokenType::Identifier, value, start_col);
}

Token Lexer::number(std::size_t start_col) {
    std::string digits;
    while (index_ < source_.size() && std::isdigit(static_cast<unsigned char>(current()))) {
        digits.push_back(advance());
    }
    if (index_ < source_.size() && current() == '.') {
        digits.push_back(advance());
        while (index_ < source_.size() && std::isdigit(static_cast<unsigned char>(current()))) {
            digits.push_back(advance());
        }
    }
    return make_token(TokenType::Number, digits, start_col);
}

Token Lexer::string_literal(std::size_t start_col) {
    std::string value;
    while (index_ < source_.size()) {
        char c = advance();
        if (c == '"') break;
        value.push_back(c);
    }
    return make_token(TokenType::StringLiteral, value, start_col);
}

Token Lexer::comment(std::size_t start_col) {
    std::string text;
    while (index_ < source_.size()) {
        char c = advance();
        if (c == '\n') break;
        text.push_back(c);
    }
    return make_token(TokenType::Comment, text, start_col);
}

}  // namespace tl::parser
