#include "Automaton.h"
#include "Grammar.h"

Automaton::Automaton(string initState, vector<string> finalSt) 
{
    initialState = initState;
    finalStates = finalSt;
}
void Automaton::addTransitions(string currSt, string tranL, string nextSt) 
{
    currentState.push_back(currSt);
    nextState.push_back(nextSt);
    transitionLabel.push_back(tranL);
    alphabet.insert(tranL);
    states.insert(nextSt);
}
void Automaton::addFinalState(string finalSt)
{
    finalStates.push_back(finalSt);
}
void Automaton::wordIsValid(string s)
{
    bool flag = true;
    int levelWord = 0, levelState = 0, count = 0;
    string check, temp = initialState;
    check.push_back(s[levelWord]);
    string finalState = finalStates.at(0);

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
    if (flag) cout << "This string belongs to the Finite Automaton" << endl;
    else cout << "This string does not belong to the Finite Automaton" << endl;
}
void Automaton::printFiniteAutomaton()
{
    cout << endl << "Finite Automaton Rules " << endl;
    cout << "Set of possible states: Q = Vn = { ";
    for (auto &i : states) {cout << i << ", ";}
    cout << "};" << endl << "Alphabet: Sigma = Vt = { ";
    for (auto &i : alphabet) {cout << i << ", ";}
    cout << "};" << endl << "Initial State: q0 = {" << initialState << "};" << endl;
    cout << "Final State: F = { ";
    for (auto &i : finalStates) {cout << i << ", ";}
    cout << "};" << endl << "Set of transitions: Delta = " << endl;
    for (int i = 0; i < currentState.size(); i++)
    {
        cout << "delta(" << currentState.at(i);
        cout << ", " << transitionLabel.at(i);
        cout << ") = {" << nextState.at(i) << "};" << endl;
    }
}
Grammar Automaton::toGrammar()
{
    Grammar G(initialState);
    for (int i = 0; i < currentState.size(); i++)
    {
        string lhs = currentState.at(i);
        string rhs = transitionLabel.at(i) + nextState.at(i);
        G.addProduction(lhs, rhs);
    }
    for (auto i : finalStates) {G.addProduction(i, "X");}
    return G;
}

void Automaton::isDeterministic()
{
    for (int i = 1; i < currentState.size(); i++)
    {
        if (currentState.at(i-1) == currentState.at(i) && transitionLabel.at(i-1) == transitionLabel.at(i))
        {
            cout << "This FA is non-deterministic" << endl;
            return;
        }
    }
    cout << "This FA is deterministic" << endl;
}
void Automaton::printGraph(string name)
{
    ofstream f;
    f.open(name, ios::out);
    f << "digraph dfa {\nrankdir=LR;\n";
    for (auto i : states) 
    {
        int count = 0;
        for (auto j : finalStates) if (i == j) count++;
        if (count == finalStates.size()) f << i << " [shape=doublecircle];\n";
        else f << i << " [shape=circle];\n";
        if (i == initialState) f << i << " [style=\"bold\"];\n";
    }
    f << "node [shape=circle];\n";
    for (int i = 0; i < currentState.size(); i++)
    {
        f << currentState.at(i) << " -> " << nextState.at(i);
        f << " [label=\"" << transitionLabel.at(i) << "\"];\n";
    }
    f << "}";
    f.close();
}
bool Automaton::findRecurrence(multimap<string,string> mp, string first, string second)
{
    for (auto i : mp)
        if (i.first == first && i.second == second) return 1;
    return 0;
}
Automaton Automaton::toDFA()
{
    multimap<string, string> checked;
    vector<string> newState;
    Automaton FA(initialState, finalStates);
    for (int i = 0; i < currentState.size(); i++)
    {
        string currSt = currentState.at(i);
        string label = transitionLabel.at(i);
        string nextSt = nextState.at(i);
        if (!findRecurrence(checked, currSt, label))
        {
            for (int j = 0; j < currentState.size(); j++)
            {
                if (i != j && currSt == currentState.at(j) && label == transitionLabel.at(j))
                {
                    nextSt.append(nextState.at(j));
                }
            }
            checked.insert({currSt, label});
            vector<string>::iterator it = find(currentState.begin(), currentState.end(), nextSt);
            if(it == currentState.end()) newState.push_back(nextSt);
            FA.addTransitions(currSt, label, nextSt);
        }
    }
    for (int k = 0; k < newState.size(); k++)
    {
        string currSt = newState.at(k);
        states.insert(currSt);
        vector<string> st;
        for (int j = 0; j < currSt.length(); j+=2)
        {
            string temp = currSt.substr(j, 2);
            st.push_back(temp);
            if (temp == finalStates.at(0)) FA.addFinalState(currSt);
        }
        for (auto label : alphabet)
        {
            string tempNextSt;
            vector<string> vecNextSt;
            for (int i = 0; i < currentState.size(); i++)
            {
                if (transitionLabel.at(i) == label)
                {
                    string tempSt = currentState.at(i);
                    vector<string>::iterator it = find(st.begin(), st.end(), tempSt);
                    if (it != st.end())
                    {
                        it = find(vecNextSt.begin(), vecNextSt.end(), nextState.at(i));
                        if (it == vecNextSt.end()) tempNextSt.append(nextState.at(i));
                        vecNextSt.push_back(nextState.at(i));
                    }
                }
            }
            if (tempNextSt.length() > 1) 
            {
                auto it = states.find(tempNextSt);
                if (it == states.end()) newState.push_back(tempNextSt);
                FA.addTransitions(currSt, label, tempNextSt);
            }
        }
    }
    cout << "\nThe NFA was converted to DFA" << endl;
    return FA;
}
