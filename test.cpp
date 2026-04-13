#include "lexer.h"
#include <iostream>
#include "parser.h"

using namespace std;

int main() {

    // Lexer Test
    string code = "(weights * 5.123213) + bias \n (weights * 10.) + 2*bias ^ this 1.12.13";

    Lexer lex = Lexer(code);

    vector<Token> tokenized = lex.tokenize();

    printTokens(tokenized);

    // AST Test
    // Left side: (5 + x)
    auto left_add = make_unique<BinOpNode>(
        "+",
        make_unique<NumNode>(5),
        make_unique<IdNode>("x")
    );

    // Right side: (y - 3)
    auto right_sub = make_unique<BinOpNode>(
        "-",
        make_unique<IdNode>("y"),
        make_unique<NumNode>(3)
    );

    // Multiply: (5 + x) * (y - 3)
    auto mult = make_unique<BinOpNode>(
        "*",
        move(left_add),
        move(right_sub)
    );

    // Right branch: (z / 2)
    auto div = make_unique<BinOpNode>(
        "/",
        make_unique<IdNode>("z"),
        make_unique<NumNode>(2)
    );

    // Full expression:
    // ((5 + x) * (y - 3)) + (z / 2)
    auto root = make_unique<BinOpNode>(
        "+",
        move(mult),
        move(div)
    );

    // Print AST
    cout << "==== AST Output ====" << endl;
    root->print();
    cout << endl;


    // TEST PARSER
    cout << "==== PARSER TEST OUTPUT ====" << endl;
    code = "(weights * 5.5) + bias";
    
    // 1. Lex the code
    Lexer lexer(code);
    vector<Token> tokens = lexer.tokenize();
    
    // 2. Parse the tokens
    Parser parser(tokens);
    auto astRoot = parser.parse();
    
    // 3. Visualize the tree
    astRoot->print();
    
    return 0;
}