#include <iostream>
#include <cctype>
#include "lexer.h"

using namespace std;

Token::Token(TokenType t, string v) : type(t), value(v) {}

Token::Token(TokenType t, char c) : type(t), value(1, c) {}

void Token::printInfo() const {
    cout << "[";

    switch(type) {
        case TokenType::NUMBER:
            cout << "NUMBER: " << value;
            break;
        case TokenType::IDENTIFIER:
            cout << "IDENTIFIER: " << value;
            break;
        case TokenType::PLUS:
            cout << "PLUS: " << value;
            break;
        case TokenType::STAR:
            cout << "STAR: " << value;
            break;
        case TokenType::END_OF_FILE:
            cout << value;
            break;
        case TokenType::LPAREN:
            cout << "LPAREN: " << value;
            break;
        case TokenType::RPAREN:
            cout << "RPAREN: " << value;
            break;
    }

    cout << "] ";
}

Lexer::Lexer(string s) : source(s) {}

vector<Token> Lexer::tokenize() {
    vector<Token> tokenized;
    size_t pos = 0;

    while (pos < source.length()) {
        char c = source[pos];

        if (isspace(c)) {
            pos++;
            continue;
        }

        if (isalpha(c)) {
            string id = "";
            while (pos < source.length() && isalnum(source[pos])) {
                id += source[pos];
                pos++;
            }
            tokenized.emplace_back(TokenType::IDENTIFIER, id);
            continue;
        }

        if (isdigit(c)) {
            string num = "";
            while (pos < source.length() && isdigit(source[pos])) {
                num += source[pos];
                pos++;
            }
            tokenized.emplace_back(TokenType::NUMBER, num);
            continue;
        }

        switch (c) {
            case '*':
                tokenized.emplace_back(TokenType::STAR, c);
                break;
            case '(':
                tokenized.emplace_back(TokenType::LPAREN, c);
                break;
            case ')':
                tokenized.emplace_back(TokenType::RPAREN, c);
                break;
            case '+':
                tokenized.emplace_back(TokenType::PLUS, c);
                break;
        }

        pos++;
    }

    tokenized.emplace_back(TokenType::END_OF_FILE, "EOF");
    return tokenized;
}

void printTokens(vector<Token> &tokens) {

    for (Token &t : tokens) {
        t.printInfo();
    }

    cout << endl;
}


int main() {

    string code = "(weights * 5) + bias + test1*test014       + (yeet1         *thisthing)";

    Lexer lex = Lexer(code);

    vector<Token> tokenized = lex.tokenize();

    printTokens(tokenized);

    return 0;
}