#include "Lexer.h"
#include <iostream>
#include <regex>

Lexer::Lexer(const string& input) : input(input) {}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;
    tokens.reserve(input.size() / 2);  // Reserve approximate memory for tokens
    
    regex tokenRegex(R"(\b(int|float)|\b(\d+)\b|\b(\w+)\b|([-+*/=]))");
    sregex_iterator regexIterator(input.begin(), input.end(), tokenRegex);
    sregex_iterator regexEnd;

    while (regexIterator != regexEnd) {
        smatch match = *regexIterator;
        string tokenValue = match.str();
        Token::Type tokenType = getTokenType(tokenValue);
        tokens.emplace_back(tokenType, tokenValue);
        ++regexIterator;
    }

    return tokens;
}

void Lexer::printTokens(const vector<Token>& tokens) {
    for (const Token& token : tokens) {
        cout << token.toString() << endl;
    }
}

Token::Type Lexer::getTokenType(const string& tokenValue) {
    if (regex_match(tokenValue, regex(R"(\d+)"))) {
        return Token::NUMBER;
    }
    else if (regex_match(tokenValue, regex(R"([-+*/=])"))) {
        return Token::OPERATOR;
    }
    else if (regex_match(tokenValue, regex(R"(\b(int|float)\b)"))) {
        return Token::KEYWORD;
    }
    else if (regex_match(tokenValue, regex(R"(\w+)"))) {
        return Token::IDENTIFIER;
    }
    else {
        return Token::UNKNOWN;
    }
}
