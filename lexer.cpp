#include <iostream>
#include <memory>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

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
    string value;

    Token() {}
    Token(TokenType t, string v) : type(t), value(v) {}
    Token(TokenType t, char c) : type(t), value(1, c) {}

    void printInfo() const {

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
                cout << "RPAREN" << value;
                break;
        }

        cout << "] ";
    }
};

class Lexer {
    public:
        string source;

        Lexer(string s) : source(s) {}

        vector<Token> tokenize() {

            vector<Token> tokenized;
            
            size_t pos = 0;

            while (pos < source.length()) {
                
                char c = source[pos];

                // Empty character
                if (isspace(c)) {
                    pos++;
                    continue;
                }

                // Identifier
                if (isalpha(c)) {
                    
                    string id = "";

                    while (pos < source.length() && isalnum(source[pos])) {
                        id += source[pos];
                        pos++;
                    }

                    tokenized.emplace_back(TokenType::IDENTIFIER, id);
                    continue;
                }

                // Number
                if (isdigit(c)) {
                    string num = "";

                    while (pos < source.length() && isdigit(source[pos])) {
                        num += source[pos];
                        pos++;
                    }

                    tokenized.emplace_back(TokenType::NUMBER, num);
                    continue;
                }

                // Special Chars
                switch (c) {
                    case '*':
                        tokenized.emplace_back(TokenType::STAR, c);
                        pos++;
                        break;
                    case '(':
                        tokenized.emplace_back(TokenType::LPAREN, c);
                        pos++;
                        break;
                    case ')':
                        tokenized.emplace_back(TokenType::RPAREN, c);
                        pos++;
                        break;
                    case '+':
                        tokenized.emplace_back(TokenType::PLUS, c);
                        pos++;
                        break;
                }
            }

            // Sentinel for EOF
            tokenized.emplace_back(TokenType::END_OF_FILE, "EOF");

            return tokenized;
        }

};

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