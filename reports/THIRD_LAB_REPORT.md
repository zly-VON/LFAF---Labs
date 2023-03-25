# Topic: Lexer & Scanner.

### Course: Formal Languages & Finite Automata
### Author: Milena Cojuhari

----

## Theory

A lexer breaks down a string into a series of tokens. The process of lexing involves scanning the input string character by character and identifying the meaning of each group of characters. 

A token is a sequence of characters that represent a single element of the language syntax, such as a keyword, identifier, operator, literal value, or punctuation mark.


## Objectives:

1. Understand what lexical analysis is.
2. Get familiar with the inner workings of a lexer/scanner/tokenizer.
3. Implement a sample lexer and show how it works.


## Implementation description

* Tokens
    * The tokens of this sample lexer are:
        * Identifier: a...z (variables)
        * Number: 0..9
        * Operator: +, -, *, /, =
        * Keyword: int, float
        * Unkown: if none of the previous tokens match
    * This function from the token class checks the type of the token and returns a string with the token name and its value, useful for printing them visually.

```
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
```

* Printing tokens of the input
    * This function iterates through the vector of tokens calling the "toString()" method. It is used to visualize the output of the lexer.

```
void Lexer::printTokens(vector<Token> tokens)
{
    cout << endl;
    for (Token token : tokens) 
    {
        cout << token.toString() << endl;
    }
}
```

* Parse Number
    * Starting from the current position (pos), this function adds each number digit to the string number until a non-digit character is encountered or the end of the input string is reached. In the end, it returns the parsed number as a string.
    * Similar functions are written for the parsing of the Identifier and Unknown characters.

```
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
```
```
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
```
```
string Lexer::parseUnknown() 
{
    string unknown(1, input[pos]);
    pos++;
    return unknown;
}
```

* Parse Operator 
    * This function takes a character as input and checks if it matches any of the operators, if yes it returns true, otherwise false.
    * A similar function is written for the parsing of the Keywords.

```
bool Lexer::isOperator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}
```
```
bool Lexer::isKeyword(string identifier) 
{
    return (identifier == "int" || identifier == "float");
}
```


* Tokenization
    * This function breaks the input string into tokens and return them as a Token vector. It starts by analyzing each character, and checking if it is a number, operator, identifier or keyword, by using the parsing functions. If it finds the match, the new token object is added to the vector of tokens, if there is no match it is added as unknown.
    * If the character is a white space, the current position is incremented.

```
vector<Token> Lexer::tokenize() 
{
    vector<Token> tokens;
    while (pos < input.size()) 
    {
        char current_char = input[pos];
        if (isdigit(current_char)) 
            tokens.push_back(Token(Token::NUMBER, parseNumber()));
        else if (isOperator(current_char)) {
            tokens.push_back(Token(Token::OPERATOR, string(1, current_char)));
            pos++;
        } 
        else if (isalpha(current_char)) {
            string identifier = parseIdentifier();
            if (isKeyword(identifier)) 
                tokens.push_back(Token(Token::KEYWORD, identifier));
            else 
                tokens.push_back(Token(Token::IDENTIFIER, identifier));
        } 
        else if (isspace(current_char)) pos++;
        else {
            string value(1, current_char);
            tokens.push_back(Token(Token::UNKNOWN, value));
            pos++;
        }
    }
    return tokens;
}
```

* Main
    * A simple arithmetic expression is passed as input to the Lexer class. Then the string is tokenized and printed as tokens to see that it worked correctly.

```
int main(void)
{
    ...

    string input = "int a = 5 + 2 * 3";
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    lexer.printTokens(tokens);

    return 0;
}
```


## Screenshots / Results

* String input 'int a = 5 + 2 * 3'
    * Every token was correctly identified.

```
KEYWORD: int
IDENTIFIER: a
OPERATOR: =
NUMBER: 5
OPERATOR: +
NUMBER: 2
OPERATOR: *
NUMBER: 3
```

* String input 'float s != 51 / 2 - 7'
    * In this example appears the UNKNOWN token for characters that did not find a match.

```
KEYWORD: float
IDENTIFIER: s
UNKNOWN: !
OPERATOR: =
NUMBER: 51
OPERATOR: /
NUMBER: 2
OPERATOR: -
NUMBER: 7
```


## Conclusions

&ensp;&ensp;&ensp; In this laboratory work I got a deeper understanding of what a Lexer is and how it can be implemented. The Lexer that I implemented was a very simple one that included the tokenization of basic arithmetic expressions. The trickest part was handling unkown characters, as they are not clearly identified. But I solved it by creating a new token type UNKNOWN. 

&ensp;&ensp;&ensp; Finally, I managed to finish this laboratory work successfully and with satisfactory results.
