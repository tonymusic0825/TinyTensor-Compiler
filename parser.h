#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>
#include "lexer.h" 

class ASTNode {
    public:
        virtual ~ASTNode() = default; 

        virtual void print(int depth = 0) const = 0;
};

class NumNode : public ASTNode {
    public:
        double value;

        NumNode(double v);

        void print(int depth = 0) const override; 
};

class IdNode : public ASTNode {
    public:
        std::string name;

        IdNode(std::string n);

        void print(int depth = 0) const override;
};

class BinOpNode : public ASTNode {
    public:
        std::string op;
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;

        BinOpNode(std::string o, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r);

        void print(int depth = 0) const override;
};

class Parser {
    public:
        std::vector<Token> tokens;
        size_t pos = 0;

        Parser(const std::vector<Token>& t);

        // Helper Functions
        Token current() const;
        void advance();
        void expect(TokenType type, std::string error_msg);

        // Grammar Methods
        std::unique_ptr<ASTNode> parseFactor();
        std::unique_ptr<ASTNode> parseTerm();
        std::unique_ptr<ASTNode> parseExpression();

        // Public interface
        std::unique_ptr<ASTNode> parse() { return parseExpression(); }


};

#endif