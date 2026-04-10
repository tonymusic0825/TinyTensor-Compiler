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
};


int main() {


    return 0;
}