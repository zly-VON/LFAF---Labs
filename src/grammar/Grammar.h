#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Grammar
{
    private:
        vector<string> nonTerminalVariables;
        vector<string> terminalVariables;

        vector<string> leftP;
        vector<string> rightP;

        string startingCharacter;

        int flag;
        string newString;
        string tempString;

    public:
        Grammar();
        void generateString();
        vector<string> toFiniteAutomaton();
        void printGrammar();
};

#endif