#pragma once 
#include<string>
#include<vector>
#include<unordered_map>
#include"Token.h"

class Scanner {
    public:
        Scanner(const std::string& source) : source{source}, keywords{
            {"and",    TokenType::AND},
            {"class",  TokenType::CLASS},
            {"else",   TokenType::ELSE},
            {"false",  TokenType::FALSE},
            {"for",    TokenType::FOR},
            {"fun",    TokenType::FUN},
            {"if",     TokenType::IF},
            {"nil",    TokenType::NIL},
            {"or",     TokenType::OR},
            {"print",  TokenType::PRINT},
            {"return", TokenType::RETURN},
            {"super",  TokenType::SUPER},
            {"this",   TokenType::THIS},
            {"true",   TokenType::TRUE},
            {"var",    TokenType::VAR},
            {"while",  TokenType::WHILE}
        } {}
        std::vector<Token> scanTokens();
    private:
        std::string source;
        std::vector<Token> tokens = {};
        const std::unordered_map<std::string, TokenType> keywords;
        void addToken(TokenType type);
        void addToken(TokenType type, const LoxValue& literal);
        bool isAtEnd() const;
        void scanToken();
        char advance();
        char peek();
        char peekNext();
        void string();
        void number();
        void identifier();
        bool match(char expected);
        int start = 0;
        int current = 0;
        int line = 1;
};