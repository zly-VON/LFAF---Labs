#ifndef TOKEN_H
#define TOKEN_H


#include <iostream>
using namespace std;

class Token 
{
    public:
        // the type of tokens of the lexer
        enum Type {IDENTIFIER, NUMBER, OPERATOR, KEYWORD, UNKNOWN};
        Token(Type type, string value);
        // coverts token to string for printing it with the value
        string toString();
        Type getType();
        string getValue();

    private:
        Type type;
        string value;
};


#endif