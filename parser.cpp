#include <string>
#include <memory>
#include <vector>
#include "parser.h"
#include <iostream> 

using namespace std;


// AST

// Number Node
NumNode::NumNode(double v) : value(v) {}

void NumNode::print(int depth) const {

    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }

    cout << '[' << "Number: " << value << ']' << endl;
} 


// Identifier Node
IdNode::IdNode(string n) : name(n) {}

void IdNode::print(int depth) const {

    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }

    cout << '[' << "Identifier: " << name << ']' << endl;
}


// Binary Operation Node
BinOpNode::BinOpNode(string o, unique_ptr<ASTNode> l, 
    unique_ptr<ASTNode> r) : op(o), left(move(l)), right(move(r)) {}

void BinOpNode::print(int depth) const {

    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }

    cout << '[' << "Binary OP: " << op << ']' << endl;

    left->print(depth + 1);
    right->print(depth + 1); 
}



// Parser
Parser::Parser(const vector<Token>& t) : tokens(t) {} 

Token Parser::current() const {
    return tokens[pos];
}

void Parser::advance() {
    pos++;
}

void Parser::expect(TokenType type, string error_msg) {
    if (current().type == type) {
        advance();
        return;
    } 

    throw runtime_error(error_msg);
}

