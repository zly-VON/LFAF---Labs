#ifndef LEXER_H
#define LEXER_H


#include "Token.h"
#include <vector>
#include <iostream>
using namespace std;

class Lexer 
{
    public:
        Lexer(string input);
        // breaks the string into tokens
        vector<Token> tokenize();
        void printTokens(vector<Token> tokens);

    private:
        string input;
        size_t pos;

        string parseNumber();
        string parseIdentifier();
        string parseUnknown();
        bool isOperator(char c);
        bool isKeyword(string identifier);
};


#endif