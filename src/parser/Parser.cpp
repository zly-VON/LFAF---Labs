#include "Parser.h"
#include <iostream>

Parser::Parser(const vector<Token>& tokens) : tokens(tokens), index(0) {}

ASTNode* Parser::parse() {
    skipKeywordsAndDeclarations();
    return parseExpression();
}

void Parser::skipKeywordsAndDeclarations() {
    while (index < tokens.size()) {
        Token currentToken = tokens[index];
        index++;

        if (currentToken.getType() == Token::OPERATOR && currentToken.getValue() == "=") {
            break;
        }
    }
}

ASTNode* Parser::parseExpression() {
    ASTNode* left = parseTerm();

    while (index < tokens.size()) {
        Token currentToken = tokens[index];

        if (currentToken.getType() == Token::OPERATOR) {
            OperatorNode* opNode = new OperatorNode(currentToken.getValue());
            index++;
            ASTNode* right = parseTerm();
            left = new BinaryExpressionNode(left, opNode, right);
        } else {
            break;
        }
    }

    return left;
}

ASTNode* Parser::parseTerm() {
    Token currentToken = tokens[index];
    index++;

    if (currentToken.getType() == Token::IDENTIFIER) {
        return new IdentifierNode(currentToken.getValue());
    } else if (currentToken.getType() == Token::NUMBER) {
        return new NumberNode(currentToken.getValue());
    } else {
        cerr << "Error: Unexpected token: " << currentToken.toString() << endl;
        return nullptr;
    }
}
