#include "Grammar.h"

Grammar::Grammar(string startChar) 
{
    startingCharacter = newString = tempString = startChar;
    flag = 0;
}
void Grammar::addProduction(string lhs, string rhs) 
{
    leftP.push_back(lhs);
    rightP.push_back(rhs);
    nonTerminalVariables.insert(lhs);
    char temp = rhs.front();
    string temp2; temp2 = temp;
    if (temp2 != "X") terminalVariables.insert(temp2);
}
void Grammar::generateString()
{
    int nr = rand() % leftP.size();
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
            nr = rand() % leftP.size();
        }
        tempString = rightP.at(nr);
        newString.pop_back();
        newString.append(tempString);
        cout << " -> " << newString;
    }
    if (isupper(newString.back())) generateString();
    else 
    {
        newString = tempString = startingCharacter;
        flag = 0;
        cout << endl;
    }
}

Automaton Grammar::toFiniteAutomaton()
{
    Automaton FA(startingCharacter, {"X"});
    for (int i = 0; i < leftP.size(); i++)
    {
        string currSt = leftP.at(i);
        string temp = rightP.at(i);
        string label, nextSt;
        label.append(1, temp.front());
        if (temp.length() > 1) nextSt.append(1, temp.back());
        else nextSt = "X";
        FA.addTransitions(currSt, label, nextSt);
    }
    return FA;
}
void Grammar::printGrammar()
{
    cout << endl << "Grammar Rules" << endl;
    cout << "Vn = { ";
    for (auto &i : nonTerminalVariables) {cout << i << ", ";}
    cout << "};" << endl << "Vt = { ";
    for (auto &i : terminalVariables) {cout << i << ", ";}
    cout << "};" << endl;
    cout << "Start character: " << startingCharacter << endl;
    cout << "Set of productions: P = " << endl;
    for (int i = 0; i < leftP.size(); i++)
        cout << leftP.at(i) << " -> " << rightP.at(i) << endl;
}
void Grammar::chomskyType()
{
    int type;
    int countLeft = 0, countRight = 0, countUpper = 0;
    string left = leftP.at(0);
    string right = rightP.at(0);
    
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

    if (type == 3) cout << "This is a Regular Grammar" << endl; 
    else if (type == 2) cout << "This is a Conntext-Free Grammar" << endl;
    else if (type == 1) cout << "This is a Context-Sensitive Grammar" << endl;
    else cout << "This is an Unrestricted Grammar" << endl;
}
