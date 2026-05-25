#pragma once
#include "TokenType.h"
#include <string>
#include <variant> 
#include <format>

using LoxValue = std::variant<std::monostate, std::string, double, bool>;
class Token {
    public:
        Token(TokenType type, const std::string& lexeme, const LoxValue& literal, int line): type{type}, lexeme{lexeme}, literal{literal}, line{line} {};
        std::string toString() const {
            return std::format("{} {} {}", static_cast<int>(type), lexeme, line);
        }
    private: 
        TokenType type;
        std::string lexeme;
        LoxValue literal;
        int line;

};