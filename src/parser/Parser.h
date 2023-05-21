#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"
#include "ASTNode.h"

class Parser {
public:
    Parser(const vector<Token>& tokens);
    ASTNode* parse();
private:
    const vector<Token>& tokens;
    size_t index;
    void skipKeywordsAndDeclarations();
    ASTNode* parseExpression();
    ASTNode* parseTerm();
};

#endif // PARSER_H
