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


// Grammer Methods
/**
 * Expression   ->   Term (+ Term)
 * Term         ->   Factor (* Factor)
 * Factor       ->   NUMBER | IDENTIFIER | (Expression)
 */
unique_ptr<ASTNode> Parser::parseFactor() {
    
    Token cur = current();
    unique_ptr<ASTNode> ret;

    switch(cur.type) {
        case TokenType::NUMBER:
            ret = make_unique<NumNode>(stod(cur.value));
            advance();
            break;
        case TokenType::IDENTIFIER:
            ret = make_unique<IdNode>(cur.value); 
            advance();
            break;
        case TokenType::LPAREN:
            advance();
            ret = parseExpression();
            expect(TokenType::RPAREN, "Expected closing ')'");
            break; 
        default:
            throw runtime_error("Unexpected token at line " + to_string(cur.line)
                + " column " + to_string(cur.column));
        }
            
    return ret;
}

unique_ptr<ASTNode> Parser::parseTerm() {

    auto left = parseFactor();

    while(current().type == TokenType::STAR) {
        string op = current().value;
        advance();
        auto right = parseFactor();
        left = make_unique<BinOpNode>(op, move(left), move(right));
    }

    return left;
}

unique_ptr<ASTNode> Parser::parseExpression() {
    
    auto left = parseTerm();

    while (current().type == TokenType::PLUS) {
        string op = current().value;
        advance();
        auto right = parseTerm();
        left = make_unique<BinOpNode>(op, move(left), move(right));
    }

    return left;
}
