#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "Grammar.h"

class FiniteAutomaton : public Grammar
{
    private:
        vector<string> states;
        vector<string> alphabet;
        string initialState;
        string finalState;

        vector<string> currentState;
        vector<string> nextState;
        vector<string> transitionLabel;
    
    public:
        FiniteAutomaton();
        bool wordIsValid(string s);
        void printFiniteAutomaton();
};

#endif