#include "Lexer.h"
#include "Grammar.h"
#include "Automaton.h"
#include <iostream>
#include <time.h>
using namespace std;

int main(void)
{
    Grammar g("S");
    g.addProduction("S", "A");
    g.addProduction("A", "aX");
    g.addProduction("A", "bX");
    g.addProduction("X", "e");
    g.addProduction("X", "BX");
    g.addProduction("X", "b");
    g.addProduction("B", "AD");
    g.addProduction("D", "aD");
    g.addProduction("D", "a");
    g.addProduction("C", "Ca");
    g.printGrammar();

    g.toChomskyNormalForm();

    return 0;
}