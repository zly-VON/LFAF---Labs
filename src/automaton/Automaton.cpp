#include "Automaton.h"

FiniteAutomaton::FiniteAutomaton()
{
    vector<string> v = Grammar::toFiniteAutomaton();
    
    states.insert(states.end(), v.begin(), v.begin() + 3);
    alphabet.insert(alphabet.end(), v.begin() + 3, v.begin() + 6);
    initialState = v.at(6);
    finalState = v.at(7);
    states.push_back(finalState);

    currentState.insert(currentState.end(), v.begin() + 8, v.begin() + 15);
    nextState.insert(nextState.end(), v.begin() + 15, v.begin() + 22);
    transitionLabel.insert(transitionLabel.end(), v.begin() + 22, v.end());
}

bool FiniteAutomaton::wordIsValid(string s)
{
    bool flag = true;
    int levelWord = 0, levelState = 0;
    string check, temp = initialState;
    check.push_back(s[levelWord]);
    
    while (levelWord < s.length() && flag)
    {
        if (currentState.at(levelState) == temp && transitionLabel.at(levelState) == check)
        {
            temp = nextState.at(levelState);
            levelState = 0;
            levelWord++;

            check.pop_back();
            check.push_back(s[levelWord]);
        }
        else levelState++;

        if (levelState > 6) flag = false;
        if (levelWord == s.length() && temp != finalState) flag = false;
    }
    
    return flag;
}

void FiniteAutomaton::printFiniteAutomaton()
{
    cout << endl;
    cout << "Finite Automaton Rules " << endl;
    cout << "Set of possible states: Q = Vn U {X} = { ";
    for (auto &i : states)
    {
        cout << i << ", ";
    }
    cout << "};" << endl;
    cout << "Alphabet: Sigma = Vt = { ";
    for (auto &i : alphabet)
    {
        cout << i << ", ";
    }
    cout << "};" << endl;
    cout << "Initial State: q0 = {" << initialState << "};" << endl;
    cout << "Final State: F = {" << finalState << "};" << endl;
    cout << "Set of transitions: Delta = " << endl;
    for (int i = 0; i < currentState.size(); i++)
    {
        cout << "delta(" << currentState.at(i);
        cout << ", " << transitionLabel.at(i);
        cout << ") = {" << nextState.at(i) << "};" << endl;
    }
    cout << endl;
}