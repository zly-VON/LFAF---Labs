# Topic: Determinism in Finite Automata. Conversion from NDFA 2 DFA. Chomsky Hierarchy.

### Course: Formal Languages & Finite Automata
### Author: Milena Cojuhari

----

## Theory
Chomsky Classification:
* Type 0. Unristricted Grammar
* Type 1. Context-Sensitive Grammar
* Type 2. Context-Free Grammar
* Type 3. Regular Grammar

Finite Automata:
* Deterministic FA
* Non-deterministic FA
* Epsilon-Nondeterministic FA

&ensp;&ensp;&ensp; A Deterministic Finite Automata (DFA) is a type of finite automata with a unique transition from each state to every input symbol.
&ensp;&ensp;&ensp; A Non-deterministic Finite Automata (NFA) is a type of finite automata that allows for multiple possible following states based on the current input.


## Objectives:

* Get familiar with NFA and DFA and Chomsky Classification for Grammar
* Implement a fucntion that could classify the grammar based on Chomsky hierarchy.
* Implement conversion of a finite automaton to a regular grammar.
* Determine whether your FA is deterministic or non-deterministic.
* Implement some functionality that would convert an NDFA to a DFA.
* Represent the finite automaton graphically.


## Implementation description

* Chomsky Classification
    * The Grammar is classified by counting the number of variables present in the LHS and RHS, and also by taking into account the reccurence of terminal variables for each side.

```
void Grammar::chomskyType()
{
    // some variables
    ...
    for (int i = 0; i < leftP.size(); i++)
    {
        if (left.length() > 1) countLeft++;
        if (right.length() > 2) countRight++;
        for (int i = 0; i < left.length(); i++)
            if (!isupper(left[i])) countUpper++;
    }
    if (!countLeft && !countRight) type = 3;
    else if (!countLeft && countRight)  type = 2;
    else if (countUpper == leftP.size()) type = 1;
    else type = 0;
    // print the type
    ...
}
```

* Conversion of Finite Automaton to Regular Grammar
    * A new Grammar is initialized and all the current rules of the FA are copied into the Grammar, the Grammar is returned in the end.

```
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
```

* Function to check if the FA is Deterministic or Non-Deterministic
    * Iterate through all transitions, if at least one state leads to more states through the same label, then the FA is Non-Deterministic, if not it is Deterministic.

```
void Automaton::isDeterministic()
{
    for (int i = 1; i < currentState.size(); i++)
        if (currentState.at(i-1) == currentState.at(i) && 
        transitionLabel.at(i-1) == transitionLabel.at(i))
        {
            cout << "This FA is non-deterministic" << endl;
            return;
        }
    cout << "This FA is deterministic" << endl;
}
```

* Conversion of NFA to DFA
    * A new automaton is initialized and all current transition of the nfa are copied into the dfa. If new states are present, the new transitions are computed based on each subset of the nfa. The resulting dfa will have a set of states that correspond to subsets of the nfa states.

```
Automaton Automaton::toDFA()
{
    // some variables
    ...
    Automaton FA(initialState, finalStates);
    for (int i = 0; i < currentState.size(); i++)
    {
        // current transition of nfa are copied to dfa
        ...
    }
    for (int k = 0; k < newState.size(); k++)
    {
        // add new states in the vector and in case update the final states
        ...
        for (auto label : alphabet)
        {
            string tempNextSt;
            vector<string> vecNextSt;
            for (int i = 0; i < currentState.size(); i++
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
            // add new current/next state and label to nfa
            ...
        }
    }
}
```

* Function to represent the Finite Automaton graphically.
    * The transitons of the FA are copied into a .dot file using the grammar of DOT language. The .dot file is compiled using Graphviz and a .png file is generated.

```
void Automaton::printGraph(string name)
{
    ofstream f;
    f.open(name, ios::out);
    f << "digraph dfa {\nrankdir=LR;\n";
    for (auto i : states) 
    {
        int flag = 0;
        for (auto j : finalStates)
            if (i == j) 
            {
                f << i << " [shape=doublecircle];\n";
                flag = 1;
            }
        if (!flag) f << i << " [shape=circle];\n";
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
```


## Screenshots / Results

According to the register ID, my variant is 12

* Chomsky Classification of the Grammar

```
Grammar Rules
Vn = { D, F, S, };
Vt = { a, b, c, };
Start character: S
Set of productions: P =
S -> aF
F -> bF
F -> cD
S -> bS
D -> cS
D -> a
F -> a
This is a Regular Grammar
```

* Conversion of Finite Automaton to Grammar
    * "X" represents that here are no more transitions

```

Finite Automaton Rules
Set of possible states: Q = Vn = { q0, q1, q2, q3, };
Alphabet: Sigma = Vt = { a, b, c, };
Initial State: q0 = {q0};
Final State: F = { q2, };
Set of transitions: Delta =
delta(q0, b) = {q0};
delta(q0, a) = {q1};
delta(q1, c) = {q1};
delta(q1, a) = {q2};
delta(q3, a) = {q1};
delta(q3, a) = {q3};
delta(q2, a) = {q3};

Grammar Rules
Vn = { q0, q1, q2, q3, };
Vt = { a, b, c, };
Start character: q0
Set of productions: P =
q0 -> bq0
q0 -> aq1
q1 -> cq1
q1 -> aq2
q3 -> aq1
q3 -> aq3
q2 -> aq3
q2 -> X
```

* Determine if the Finite Automaton is an NFA or DFA

```
Finite Automaton Rules
Set of possible states: Q = Vn = { q0, q1, q2, q3, };
Alphabet: Sigma = Vt = { a, b, c, };
Initial State: q0 = {q0};
Final State: F = { q2, };
Set of transitions: Delta =
delta(q0, b) = {q0};
delta(q0, a) = {q1};
delta(q1, c) = {q1};
delta(q1, a) = {q2};
delta(q3, a) = {q1};
delta(q3, a) = {q3};
delta(q2, a) = {q3};
This FA is non-deterministic
```

* Conversion of the previous NFA to DFA

```
The NFA was converted to DFA

Finite Automaton Rules
Set of possible states: Q = Vn = { q0, q1, q1q3, q2, q2q1q3, q3, };
Alphabet: Sigma = Vt = { a, b, c, };
Initial State: q0 = {q0};
Final State: F = { q2, q2q1q3, };
Set of transitions: Delta =
delta(q0, b) = {q0};
delta(q0, a) = {q1};
delta(q1, c) = {q1};
delta(q1, a) = {q2};
delta(q3, a) = {q1q3};
delta(q2, a) = {q3};
delta(q1q3, a) = {q2q1q3};
delta(q1q3, c) = {q1};
delta(q2q1q3, a) = {q2q1q3};
delta(q2q1q3, c) = {q1};
This FA is deterministic
```

* Graph of NFA

```
// nfa.dot

digraph dfa {
rankdir=LR;
q0 [shape=circle];
q0 [style="bold"];
q1 [shape=circle];
q2 [shape=doublecircle];
q3 [shape=circle];
node [shape=circle];
q0 -> q0 [label="b"];
q0 -> q1 [label="a"];
q1 -> q1 [label="c"];
q1 -> q2 [label="a"];
q3 -> q1 [label="a"];
q3 -> q3 [label="a"];
q2 -> q3 [label="a"];
}
```
<p align="left">
  <img src="..\images\nfa.png">
</p>


* Graph of DFA

```
// dfa.dot

digraph dfa {
rankdir=LR;
q0 [shape=circle];
q0 [style="bold"];
q1 [shape=circle];
q1q3 [shape=circle];
q2 [shape=doublecircle];
q2q1q3 [shape=doublecircle];
q3 [shape=circle];
node [shape=circle];
q0 -> q0 [label="b"];
q0 -> q1 [label="a"];
q1 -> q1 [label="c"];
q1 -> q2 [label="a"];
q3 -> q1q3 [label="a"];
q2 -> q3 [label="a"];
q1q3 -> q2q1q3 [label="a"];
q1q3 -> q1 [label="c"];
q2q1q3 -> q2q1q3 [label="a"];
q2q1q3 -> q1 [label="c"];
}
```
<p align="left">
  <img src="..\images\dfa_corrected.png">
</p>


## Conclusions

&ensp;&ensp;&ensp; In this laboratory work I got a deeper understanding of Finite Automaton and its classification. The trickiest part was converting my thoughts into code. While I had a lot of ideas of how to convert a nfa to dfa, implementing it was more challenging. Even though I encountered different difficulties, I managed to find a solution to most of them and succesfully completed the tasks.
