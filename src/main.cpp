#include "Lexer.h"
#include "Grammar.h"
#include "Automaton.h"
#include <iostream>
#include <time.h>
using namespace std;

int main(void)
{
    srand(time(0));    
    
    Grammar g("S");
    g.addProduction("S", "aF");
    g.addProduction("F", "bF");
    g.addProduction("F", "cD");
    g.addProduction("S", "bS");
    g.addProduction("D", "cS");
    g.addProduction("D", "a");
    g.addProduction("F", "a");
    g.printGrammar();
    g.chomskyType();
    
    Automaton nfa("q0", {"q2"});
    nfa.addTransitions("q0", "b", "q0");
    nfa.addTransitions("q0", "a", "q1");
    nfa.addTransitions("q1", "c", "q1");
    nfa.addTransitions("q1", "a", "q2");
    nfa.addTransitions("q3", "a", "q1");
    nfa.addTransitions("q3", "a", "q3");
    nfa.addTransitions("q2", "a", "q3");
    nfa.printFiniteAutomaton();
    nfa.isDeterministic();
    nfa.printGraph("nfa.dot");

    Grammar g2 = nfa.toGrammar();
    g2.printGrammar();

    Automaton dfa = nfa.toDFA();
    dfa.printFiniteAutomaton();
    dfa.isDeterministic();
    dfa.printGraph("dfa.dot");


    string input = "int a = 5 + 2 * 3";
    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();
    lexer.printTokens(tokens);

    return 0;
}
