#include "Token.h"

Token::Token(Type type, const string& value) : type(type), value(value) {}

string Token::toString() const {
    switch (type) {
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

Token::Type Token::getType() const {
    return type;
}

const string& Token::getValue() const {
    return value;
}
