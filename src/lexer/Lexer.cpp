#include "Lexer.h"
    
Lexer::Lexer(string input) : input(input), pos(0) {}
// breaks the string into tokens
vector<Token> Lexer::tokenize() 
{
    vector<Token> tokens;
    while (pos < input.size()) 
    {
        char current_char = input[pos];
        if (isdigit(current_char)) 
        {
            tokens.push_back(Token(Token::NUMBER, parseNumber()));
        } 
        else if (isOperator(current_char)) 
        {
            tokens.push_back(Token(Token::OPERATOR, string(1, current_char)));
            pos++;
        } 
        else if (isalpha(current_char)) 
        {
            string identifier = parseIdentifier();
            if (isKeyword(identifier)) 
            {
                tokens.push_back(Token(Token::KEYWORD, identifier));
            } 
            else 
            {
                tokens.push_back(Token(Token::IDENTIFIER, identifier));
            }
        } 
        else if (isspace(current_char)) 
        {
            pos++;
        } 
        else 
        {
            string value(1, current_char);
            tokens.push_back(Token(Token::UNKNOWN, value));
            pos++;
        }
    }
    return tokens;
}
void Lexer::printTokens(vector<Token> tokens)
{
    cout << endl;
    for (Token token : tokens) 
    {
        cout << token.toString() << endl;
    }
}
string Lexer::parseNumber() 
{
    string number;
    while (pos < input.size() && isdigit(input[pos])) 
    {
        number += input[pos];
        pos++;
    }
    return number;
}
string Lexer::parseIdentifier() 
{
    string identifier;
    while (pos < input.size() && isalnum(input[pos])) 
    {
        identifier += input[pos];
        pos++;
    }
    return identifier;
}
string Lexer::parseUnknown() 
{
    string unknown(1, input[pos]);
    pos++;
    return unknown;
}
bool Lexer::isOperator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}
bool Lexer::isKeyword(string identifier) 
{
    return (identifier == "int" || identifier == "float");
}