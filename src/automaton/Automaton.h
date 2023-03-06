#ifndef AUTOMATON_H
#define AUTOMATON_H


#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Grammar;

class Automaton
{
    private:
        set<string> states;
        set<string> alphabet;
        string initialState;
        vector<string> finalStates;

        vector<string> currentState;
        vector<string> nextState;
        vector<string> transitionLabel;
    
    public:
        Automaton(string initState, vector<string> finalSt);
        void addTransitions(string currSt, string tranL, string nextSt);
        void addFinalState(string finalSt);
        void wordIsValid(string s);
        void printFiniteAutomaton();
        Grammar toGrammar();
        void isDeterministic();
        void printGraph(string name);
        bool findRecurrence(multimap<string,string> mp, string first, string second);
        Automaton toDFA();
};


#endif
