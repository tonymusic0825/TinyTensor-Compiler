#include "lexer.h"
#include <iostream>

using namespace std;

int main() {

    string code = "(weights * 5.123213) + bias \n (weights * 10.) + 2*bias ^ this 1.12.13";

    Lexer lex = Lexer(code);

    vector<Token> tokenized = lex.tokenize();

    printTokens(tokenized);

    return 0;
}