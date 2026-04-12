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

        void print(int depth = 0) const override; 
};

class IdNode : public ASTNode {
    public:
        std::string name;

        void print(int depth = 0) const override;
};

class BinOpNode : public ASTNode {
    public:
        std::string op;
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;

        void print(int depth = 0) const override;
};

class Parser {
    public:
        std::vector<Token> tokens;
};

#endif