#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using namespace std;

class Token {
public:
    enum Type { IDENTIFIER, NUMBER, OPERATOR, KEYWORD, UNKNOWN };
    Token(Type type, const string& value);
    string toString() const;
    Type getType() const;
    const string& getValue() const;
private:
    Type type;
    string value;
};

#endif // TOKEN_H
