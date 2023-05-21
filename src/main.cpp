#include <iostream>
#include "Lexer.h"
#include "Parser.h"
using namespace std;

int main(void) {
    string input = "float s = 10 / 6 + a";
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
