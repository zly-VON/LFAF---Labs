#ifndef GRAMMAR_H
#define GRAMMAR_H


#include "Automaton.h"
#include <iostream>
#include <set>
#include <vector>
#include <cctype>
using namespace std;

class Grammar
{
    private:
        set<string> nonTerminalVariables;
        set<string> terminalVariables;
        vector<string> leftP;
        vector<string> rightP;

        string startingCharacter;

        int flag;
        string newString;
        string tempString;

    public:
        Grammar(string startChar);
        void addProduction(string lhs, string rhs);
        void generateString();
        Automaton toFiniteAutomaton();
        void printGrammar();
        void chomskyType();
        void printIntermediaryCNF();
        void toChomskyNormalForm();
        void eliminateNullProductions();
        void eliminateUnitProductions();
        void eliminateUselessSymbols();
        void eliminateNonProductiveProductions();
        void eliminateMixedProductions();
};

#endif