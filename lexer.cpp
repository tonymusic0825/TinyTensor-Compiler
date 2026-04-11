#include <iostream>
#include <cctype>
#include "lexer.h"

using namespace std;

Token::Token(TokenType t, string v, size_t l, size_t c) : type(t), value(v), line(l), column(c) {}

Token::Token(TokenType t, char v, size_t l, size_t c) : type(t), value(1, v), line(l), column(c) {}

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
        case TokenType::UNKNOWN:
            cout << "UNKNOWN: " << value;
            break;
    }

    cout << " @ " << line << ":" << column;

    cout << "] ";
}

Lexer::Lexer(string s) : source(s) {}

vector<Token> Lexer::tokenize() {
    vector<Token> tokenized;
    size_t pos = 0;
    size_t cur_line = 1;
    size_t cur_col = 1;

    while (pos < source.length()) {
        char c = source[pos];

        if (c == ' ') {
            pos++;
            cur_col++;
            continue;
        }

        if (c == '\n') {
            pos++;
            cur_line++;
            cur_col = 0;
            continue;
        }

        if (isalpha(c)) {
            size_t temp_pos = pos;
            string id = "";
            while (pos < source.length() && isalnum(source[pos])) {
                id += source[pos];
                pos++;
            }
            tokenized.emplace_back(TokenType::IDENTIFIER, id, cur_line, cur_col);
            cur_col += pos - temp_pos;
            continue;
        }

        if (isdigit(c)) {
            size_t temp_pos = pos;
            string num = "";
            bool float_num = false;

            while (pos < source.length()) {
                
                if (source[pos] == '.' && float_num) {
                    // We let the outer loop handle invalid float
                    break; 
                }

                if (source[pos] == '.') {
                    float_num = true;
                    num += source[pos];
                    pos++;
                    continue;
                } else if (isdigit(source[pos])) {
                    num += source[pos];
                    pos++;
                    continue;
                } else {
                    break; 
                }
            }

            // If the number ended with decimal '.' we will add 0 at the end
            if (num[num.length() - 1] == '.') {
                num += '0';
            }

            tokenized.emplace_back(TokenType::NUMBER, num, cur_line, cur_col);
            cur_col += pos - temp_pos;
            continue;
        }

        switch (c) {
            case '*':
                tokenized.emplace_back(TokenType::STAR, c, cur_line, cur_col);
                break;
            case '(':
                tokenized.emplace_back(TokenType::LPAREN, c, cur_line, cur_col);
                break;
            case ')':
                tokenized.emplace_back(TokenType::RPAREN, c, cur_line, cur_col);
                break;
            case '+':
                tokenized.emplace_back(TokenType::PLUS, c, cur_line, cur_col);
                break;
            default: // Hit an unknown character
                tokenized.emplace_back(TokenType::UNKNOWN, c, cur_line, cur_col);
                cout << "Lexical Error: Unrecognized character '" 
                    << c << "' at Line " << cur_line << ", Col " << cur_col << endl;
        }

        pos++;
        cur_col++;
    }

    tokenized.emplace_back(TokenType::END_OF_FILE, "EOF", cur_line, cur_col);
    return tokenized;
}

void printTokens(vector<Token> &tokens) {

    for (Token &t : tokens) {
        t.printInfo();
    }

    cout << endl;
}
