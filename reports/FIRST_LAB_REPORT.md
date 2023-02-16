# Topic: Intro to formal languages. Regular grammars. Finite Automata.

### Course: Formal Languages & Finite Automata
### Author: Milena Cojuhari

----

## Theory
A grammar G is an ordered quadruple that contains the following elements:
* Vn - set of non-terminal symbols;
* Vt - set of terminal symbols;
* S - start symbol;
* P - set of productions;

An automaton is a mathematical model of a finite-state machine. An automaton is a 5-tuple that contains the following elements:
* Q - set of states;
* Σ - alphabet;
* δ - set of transitions;
* q0 - initial state;
* F - final state;


## Objectives:

* Create a repository on Github.
* Implement a type/class for your grammar;
* Add one function that would generate 5 valid strings from the language expressed by the given grammar;
* Implement some functionality that would convert and object of type Grammar to one of type Finite Automaton;
* For the Finite Automaton, add a method that checks if an input string can be obtained via the state transition from it;
* Write the report.


## Implementation description

* Main - here the grammar and automaton class are initialized. The rules of the regular grammar are printed to make them visibile on the console. Then, 5 strings from the grammar are generated. Next, the grammar is converted to finite automaton, that is also printed on the console to make it easier to see the process. Finally, a word is required to be inputed and it is checked if it is part of the finite automaton rules.

```
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
```

* Function to generate a string - from the starting character, it is randomly chosen from the left part of the set of solutions (if the starting character is repeated) one of them and the right part of the set of productions is added to the string. Now, the starting character becomes the upper letter from the right part of the set of productions. This function is called recursively until there are no more possibilities to continue.

```
void Grammar::generateString()
{
    int nr = rand() % 6;

    if (!flag) 
    {
        cout << startingCharacter;
        flag = 1;
    }
    
    if (isupper(newString.back()) || tempString == startingCharacter)
    {
        string temp;
        temp.push_back(tempString.back());
        while (leftP.at(nr) != temp)
        {
            nr = rand() % 6;
        }

        tempString = rightP.at(nr);
        newString.pop_back();
        newString.append(tempString);
        cout << " -> " << newString;
    }

    if (isupper(newString.back()))
        generateString();
    else 
    {
        newString = tempString = startingCharacter;
        flag = 0;
        cout << endl;
    }
}
```

* Function to convert the Regular Grammar to a Finite Automaton - the set of non-terminal symbols, the set of terminal symbols , the start symbol and the set of productions are all stored inside a vector that is passed to the constructor of the automaton class (the right parrt of the set of productions was devided in two separate strings). There, the vector is read in order an saved in the set of states, the alphabet, the set of transitions, the initial state, and for the final state we add "X".

```
vector<string> Grammar::toFiniteAutomaton()
{
    vector<string> v;
    v.insert(v.end(), nonTerminalVariables.begin(), nonTerminalVariables.end());
    v.insert(v.end(), terminalVariables.begin(), terminalVariables.end());
    v.push_back(startingCharacter);
    v.push_back("X");
    v.insert(v.end(), leftP.begin(), leftP.end());
    
    vector<string> vt;
    vector<string> vn;
    for (auto &i : rightP)
    {
        string temp;
        if (i.length() > 1)
        {
            temp = i.front();
            vt.push_back(temp);
            temp = i.back();
            vn.push_back(temp);
        }
        else 
        {
            vt.push_back(i);
            vn.push_back("X");
        } 
    }
    v.insert(v.end(), vn.begin(), vn.end());
    v.insert(v.end(), vt.begin(), vt.end());
    return v;
}
```

* Function to check if a word is valid - from the starting character, every letter of the word is checked, if it is the same as the transition label of the current state, then the next state becomes the actual current state. Once every letter is checked and the final state is reached, the word is valid. If every letter takes part of the transitions, but the last one does not meet the final state, the word is not valid. In all other cases the word is not valid.

```
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
```

## Screenshots / Results

* The Regular Grammar Rule of my variant (12) printed on the console: 
<p align="left">
  <img src="..\images\image1.png" width="200">
</p>

* The 5 strings generated from the grammar:
<p align="left">
  <img src="..\images\image2.png" width="800">
</p>

* The conversion of the Regular Grammar to Finite Automaton:
<p align="left">
  <img src="..\images\image3.png" width="450">
</p>

* Checking if a word belongs to the Finite Automaton:
<p align="left">
  <img src="..\images\image4.png" width="350">
</p>
<p align="left">
  <img src="..\images\image5.png" width="400">
</p>

## Conclusions 

In this laboratory work I understood better the meaning of a Formal Language and how a Regular Grammar can be used to create new strings from its rules. The most difficult part was understanding what it is a Finite Automaton. But once figured it out, it was not difficult to write the conversion from the Grammar. Also, even though at the start it was a bit confusing, having the set of transition made it very easy to check if a word belongs or not to the Finite Automaton.
