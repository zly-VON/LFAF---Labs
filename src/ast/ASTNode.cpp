#include "ASTNode.h"

IdentifierNode::IdentifierNode(const string& name) : name(name) {}

string IdentifierNode::toString() const {
    return "IdentifierNode: " + name;
}

NumberNode::NumberNode(const string& value) : value(value) {}

string NumberNode::toString() const {
    return "NumberNode: " + value;
}

OperatorNode::OperatorNode(const string& op) : op(op) {}

string OperatorNode::toString() const {
    return "OperatorNode: " + op;
}

BinaryExpressionNode::BinaryExpressionNode(ASTNode* left, OperatorNode* op, ASTNode* right)
    : left(left), op(op), right(right) {}

BinaryExpressionNode::~BinaryExpressionNode() {
    delete left;
    delete op;
    delete right;
}

string BinaryExpressionNode::toString() const {
    return "BinaryExpressionNode: (" + left->toString() + " " + op->toString() + " " + right->toString() + ")";
}
