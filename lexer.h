#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    NUMBER,         // (e.g. 42, 142)
    IDENTIFIER,     // (e.g. weights, input_A)
    PLUS,           // '+'
    STAR,           // '*'
    LPAREN,         // '('
    RPAREN,         // ')'
    END_OF_FILE     // EOF 
};

struct Token {
    TokenType type;
    std::string value;

    Token() {};
    Token(TokenType t, std::string v);
    Token(TokenType t, char c);

    void printInfo() const;
};

class Lexer {
    public:
        std:: string source;

        Lexer(std::string s);
        std::vector<Token> tokenize();
};

void printTokens(std::vector<Token> &tokens);

#endif