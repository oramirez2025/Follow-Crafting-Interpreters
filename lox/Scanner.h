#pragma once 
#include<string>
#include<vector>
#include<unordered_map>
#include"Token.h"

class Scanner {
    public:
        Scanner(const std::string& source) : source{source} {};
        std::vector<Token> scanTokens();
    private:
        std::string source;
        std::vector<Token> tokens = {};
        void addToken(TokenType type);
        void addToken(TokenType type, const LoxValue& literal);
        bool isAtEnd() const;
        void scanToken();
        char advance();
        char peek();
        char peekNext();
        void string();
        void number();
        bool match(char expected);
        int start = 0;
        int current = 0;
        int line = 1;
};