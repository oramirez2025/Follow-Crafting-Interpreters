#include"Scanner.h"
#include"TokenType.h"
#include"main.cpp"

std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back(Token(TokenType::END_OF_FILE, "", std::monostate(), line));
    return tokens;
}

bool Scanner::isAtEnd() const {
    return current >= source.size();
}
char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source.at(current);
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;
        case '!': addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/': 
            if (match('/')) {
                while (peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            line++;
            break;
        case '"': string(); break;
        default:
            if (isDigit(c)) {
                number();
            } else {
                error(line, "Unexpected character.");
                break;
            }
    }
}

char Scanner::peekNext() {
    if (current + 1 >= source.size()) return '\0';
    return source.at(current + 1);
}

void Scanner::number() {
    while (isDigit(peek())) advance();

    if (peek() == '.' && isDigit(peekNext())) {
        advance();
        while (isDigit(peek())) advance();
    }
    addToken(
        TokenType::NUMBER, 
        std::stod(source.substr(start, current))
    );
}

char Scanner::advance() {
    return source.at(current++);
}
bool isDigit(char c) {
    return '0' <= c && c <= '9';
}
void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }
    if (isAtEnd()) {
        error(line, "unterminated string");
        return;
    }
    advance();
    std::string value = source.substr(start + 1, current - 1);
    addToken(TokenType::STRING, value);
}

void Scanner::addToken(TokenType type) {
    addToken(type, std::monostate());
}

void Scanner::addToken(TokenType type, const LoxValue& literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;

    current++;
    return true;


}