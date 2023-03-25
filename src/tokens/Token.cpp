#include "Token.h"

Token::Token(Type type, string value) : type(type), value(value) {}
string Token::toString() 
{
    switch(type) 
    {
        case IDENTIFIER:
            return "IDENTIFIER: " + value;
        case NUMBER:
            return "NUMBER: " + value;
        case OPERATOR:
            return "OPERATOR: " + value;
        case KEYWORD:
            return "KEYWORD: " + value;
        default:
            return "UNKNOWN: " + value;
    }
}
Token::Type Token::getType() 
{ 
    return type; 
}
string Token::getValue() 
{ 
    return value; 
}
