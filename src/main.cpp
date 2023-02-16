#include "Grammar.h"
#include "Automaton.h"
#include <time.h>
#include <iostream>
using namespace std;

int main(void)
{
    srand(time(0));
    Grammar grammar;
    grammar.printGrammar();

    cout << "Generate strings from the Grammar: " << endl;
    grammar.generateString();
    grammar.generateString();
    grammar.generateString();
    grammar.generateString();
    grammar.generateString();
    
    FiniteAutomaton FA;
    grammar.toFiniteAutomaton();

    FA.printFiniteAutomaton();

    string word;
    cout << "\nEnter the string you want to check: ";
    cin >> word;
    if (FA.wordIsValid(word)) cout << "This string belongs to the Finite Automaton" << endl;
    else cout << "This string does not belong to the Finite Automaton" << endl;
    cout << endl;
    
    return 0;
}