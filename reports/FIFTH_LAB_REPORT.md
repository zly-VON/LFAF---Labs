# Topic: Parser & Building an Abstract Syntax Tree

### Course: Formal Languages & Finite Automata
### Author: Milena Cojuhari

----

## Theory

&ensp;&ensp;&ensp; A parser is a software component or tool that takes input in the form of a sequence of characters (typically a program's source code) and analyzes its structure according to a specified grammar. The parser breaks down the input into smaller components called tokens and checks if they adhere to the grammar rules.

&ensp;&ensp;&ensp; An abstract syntax tree (AST), also known as a parse tree, is a hierarchical representation of the syntactic structure of the source code provided to a parser. It captures the essential elements and their relationships, abstracting away the specific details of the language syntax. The AST organizes the program into a tree-like structure where each node represents a syntactic construct, such as a statement, expression, or declaration.


## Objectives:

1. Get familiar with parsing, what it is and how it can be programmed.
2. Get familiar with the concept of AST.
3. In addition to what has been done in the 3rd lab work do the following:
   1. In case you didn't have a type that denotes the possible types of tokens you need to:
      1. Have a type *TokenType* (like an enum) that can be used in the lexical analysis to categorize the tokens. 
      2. Please use regular expressions to identify the type of the token.
   2. Implement the necessary data structures for an AST that could be used for the text you have processed in the 3rd lab work.
   3. Implement a simple parser program that could extract the syntactic information from the input text.


## Implementation description

* __Regular Expressions__
    * Since I already had a TokenType in the 3rd lab, I did not need to add it.
    * But I had to implement the use of regular expressions to identify the type of token.

```
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
```

* __AST Node__
    * The ASTNode class serves as an abstract base class for all nodes in the Abstract Syntax Tree (AST). It provides a common interface for working with different types of AST nodes. 
    * __*virtual ~ASTNode() {}*__: This is a virtual destructor for the ASTNode class. It ensures that the proper destructors of derived classes are called when deleting an ASTNode pointer.
    * __*virtual string toString() const = 0__;*: This pure virtual function requires derived classes to implement their own version of toString(). It returns a string representation of the AST node. Each derived class provides its own implementation of toString() to represent the specific type of node and its associated data.

```
class ASTNode {
public:
    virtual ~ASTNode() {}
    virtual string toString() const = 0;
};
```

* __Identifier Node__
    * __*IdentifierNode(const string& name)*__: This is the constructor for the IdentifierNode class. It initializes the name member variable with the provided identifier name.
    * __*string toString() const override*__: This function overrides the toString() function of the base ASTNode class. It returns a string representation of the IdentifierNode, indicating that it is an identifier node and includes the identifier name.

```
IdentifierNode::IdentifierNode(const string& name) : name(name) {}

string IdentifierNode::toString() const {
    return "IdentifierNode: " + name;
}
```

* __Number Node__
    * __*NumberNode(const string& value)*__: This is the constructor for the NumberNode class. It initializes the value member variable with the provided numeric value.
    * __*string toString() const override*__: This function overrides the toString() function of the base ASTNode class. It returns a string representation of the NumberNode, indicating that it is a number node and includes the numeric value.

```
NumberNode::NumberNode(const string& value) : value(value) {}

string NumberNode::toString() const {
    return "NumberNode: " + value;
}
```

* __*Operator Node*__
    * __*OperatorNode(const string& op)*__: This is the constructor for the OperatorNode class. It initializes the op member variable with the provided operator.
    * __*string toString() const override*__: This function overrides the toString() function of the base ASTNode class. It returns a string representation of the OperatorNode, indicating that it is an operator node and includes the operator symbol.

```
OperatorNode::OperatorNode(const string& op) : op(op) {}

string OperatorNode::toString() const {
    return "OperatorNode: " + op;
}
```

* __*Binary Expression Node*__
    * __*BinaryExpressionNode(ASTNode* left, OperatorNode* op, ASTNode* right)*__: This is the constructor for the BinaryExpressionNode class. It takes pointers to the left and right operands, as well as the operator, and initializes the corresponding member variables.
    * __*~BinaryExpressionNode()*__: This is the destructor for the BinaryExpressionNode class. It is responsible for freeing the memory of the left, right, and operator nodes.
    * __*string toString() const override*__: This function overrides the toString() function of the base ASTNode class. It returns a string representation of the BinaryExpressionNode, indicating that it is a binary expression node. It includes the string representations of the left operand, operator, and right operand.

```
BinaryExpressionNode::BinaryExpressionNode(ASTNode* left, OperatorNode* op, ASTNode* right)
    : left(left), op(op), right(right) {}

BinaryExpressionNode::~BinaryExpressionNode() {
    delete left;
    delete op;
    delete right;
}

string BinaryExpressionNode::toString() const {
    return "BinaryExpressionNode: (" + left->toString() + " " + op->toString() + " " + right->toString() + ")";
}
```

* __*Parser*__
    * __*ASTNode* parse()*__: This function initiates the parsing process. It starts by calling the skipKeywordsAndDeclarations() function to skip any keywords and declarations in the token stream. Then, it calls the parseExpression() function to parse and construct the AST for the expression. Finally, it returns the root of the constructed AST.

```
ASTNode* Parser::parse() {
    skipKeywordsAndDeclarations();
    return parseExpression();
}
```

*
    * __*void skipKeywordsAndDeclarations()*__: This function is responsible for skipping any keywords and declarations encountered in the token stream. It iterates through the tokens, incrementing the index, until it finds an operator token with the value "=".

```
void Parser::skipKeywordsAndDeclarations() {
    while (index < tokens.size()) {
        Token currentToken = tokens[index];
        index++;

        if (currentToken.getType() == Token::OPERATOR && currentToken.getValue() == "=") {
            break;
        }
    }
}
```

*
    * __*ASTNode* parseExpression()*__: This function parses and constructs the AST for an expression. It starts by parsing the leftmost term using the parseTerm() function. Then, it enters a loop where it checks if the current token is an operator. If it is, it creates an OperatorNode with the current token's value and advances the index. It then parses the next term using parseTerm() and constructs a BinaryExpressionNode with the left term, operator node, and right term. The newly constructed node becomes the new left term for the next iteration. The loop continues until there are no more operator tokens or the end of the token stream is reached. Finally, it returns the root of the expression AST.

```
ASTNode* Parser::parseExpression() {
    ASTNode* left = parseTerm();

    while (index < tokens.size()) {
        Token currentToken = tokens[index];

        if (currentToken.getType() == Token::OPERATOR) {
            OperatorNode* opNode = new OperatorNode(currentToken.getValue());
            index++;
            ASTNode* right = parseTerm();
            left = new BinaryExpressionNode(left, opNode, right);
        } else {
            break;
        }
    }

    return left;
}
```

*
    * __*ASTNode* parseTerm()*__: This function parses and constructs the AST for a term. It retrieves the current token, advances the index, and checks the token's type. If it is an identifier, it creates an IdentifierNode with the token's value. If it is a number, it creates a NumberNode with the token's value. If it is neither, it prints an error message to std::cerr and returns nullptr. In each case, it returns the constructed node representing the parsed term.

```
ASTNode* Parser::parseTerm() {
    Token currentToken = tokens[index];
    index++;

    if (currentToken.getType() == Token::IDENTIFIER) {
        return new IdentifierNode(currentToken.getValue());
    } else if (currentToken.getType() == Token::NUMBER) {
        return new NumberNode(currentToken.getValue());
    } else {
        cerr << "Error: Unexpected token: " << currentToken.toString() << endl;
        return nullptr;
    }
}

```

* __*Main*__
    * This is the entry point of the program. It creates an instance of the Lexer class, tokenizes the input code, and prints the tokens. Then, it creates an instance of the Parser class, passes the tokens to it, and calls the parse() method to build the AST. If the root of the AST is successfully constructed, it prints the AST.

```
int main(void) {
    string input = "int a = 10 / 5 + 3";
    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    lexer.printTokens(tokens);

    Parser parser(tokens);
    ASTNode* root = parser.parse();
    if (root) {
        cout << "AST: " << root->toString() << endl;
        delete root;
    }

    return 0;
}
```


## Screenshots / Results

* String input 'int a = 5 * 4 / 2'
    * Every token was correctly identified.

```
KEYWORD: int
IDENTIFIER: a
OPERATOR: =
NUMBER: 5
OPERATOR: *
NUMBER: 4
OPERATOR: /
NUMBER: 2
AST: BinaryExpressionNode: (BinaryExpressionNode: (NumberNode: 5 OperatorNode: * NumberNode: 4) OperatorNode: / NumberNode: 2)
```

* String input 'float s = 10 / 6 + 3'
    * In this example appears the UNKNOWN token for characters that did not find a match.

```
KEYWORD: float
IDENTIFIER: s
OPERATOR: =
NUMBER: 10
OPERATOR: /
NUMBER: 6
OPERATOR: +
NUMBER: 3
AST: BinaryExpressionNode: (BinaryExpressionNode: (NumberNode: 10 OperatorNode: / NumberNode: 6) OperatorNode: + NumberNode: 3)
```


## Conclusions

&ensp;&ensp;&ensp; In conclusion, the laboratory work involved the implementation of a simple parser and Abstract Syntax Tree (AST) representation for parsing and analyzing arithmetic expressions. The code was organized into separate classes, each responsible for a specific aspect of the parsing process.

&ensp;&ensp;&ensp; The ASTNode and its derived classes (IdentifierNode, NumberNode, OperatorNode, and BinaryExpressionNode) formed the backbone of the AST, providing a hierarchical structure to represent the parsed expressions. These classes implemented their own toString() functions to generate string representations of the corresponding nodes.

&ensp;&ensp;&ensp; The Parser class undertook the task of constructing the AST from the token stream generated by the lexer. It used recursive descent parsing to analyze the grammar and build the AST nodes accordingly. The Parser class provided functions to skip keywords and declarations and to parse expressions and terms.

&ensp;&ensp;&ensp; Overall, the laboratory work demonstrated the process of tokenization, parsing, and constructing an AST for arithmetic expressions. It showcased the importance of organizing code into separate classes, each responsible for a specific aspect of the parsing process. The resulting AST can serve as a foundation for further analysis, optimization, or code generation tasks related to the parsed expressions.