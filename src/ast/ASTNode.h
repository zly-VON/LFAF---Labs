#ifndef ASTNODE_H
#define ASTNODE_H

#include <string>
using namespace std;

class ASTNode {
public:
    virtual ~ASTNode() {}
    virtual string toString() const = 0;
};

class IdentifierNode : public ASTNode {
public:
    IdentifierNode(const string& name);
    string toString() const override;
private:
    string name;
};

class NumberNode : public ASTNode {
public:
    NumberNode(const string& value);
    string toString() const override;
private:
    string value;
};

class OperatorNode : public ASTNode {
public:
    OperatorNode(const string& op);
    string toString() const override;
private:
    string op;
};

class BinaryExpressionNode : public ASTNode {
public:
    BinaryExpressionNode(ASTNode* left, OperatorNode* op, ASTNode* right);
    ~BinaryExpressionNode();
    string toString() const override;
private:
    ASTNode* left;
    OperatorNode* op;
    ASTNode* right;
};

#endif // ASTNODE_H
