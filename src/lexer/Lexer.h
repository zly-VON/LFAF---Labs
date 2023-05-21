#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
public:
    Lexer(const string& input);
    vector<Token> tokenize();
    void printTokens(const vector<Token>& tokens);
private:
    string input;
    Token::Type getTokenType(const string& tokenValue);
};

#endif // LEXER_H
