#include "lexer.h"
#include <iostream>

using namespace std;

int main() {

    string code = "(weights * 5) + bias + test1*test014       + (yeet1         *thisthing)";

    Lexer lex = Lexer(code);

    vector<Token> tokenized = lex.tokenize();

    printTokens(tokenized);

    return 0;
}