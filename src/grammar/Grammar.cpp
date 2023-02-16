#include "Grammar.h"

Grammar::Grammar()
{
    nonTerminalVariables = {"S", "F", "D"};
    terminalVariables = {"a", "b", "c"};
    startingCharacter = newString = tempString = "S";

    leftP = {"S", "F", "F", "S", "D", "D", "F"};
    rightP = {"aF", "bF", "cD", "bS", "cS", "a", "a"};

    flag = 0;
}

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

void Grammar::printGrammar()
{
    cout << endl;
    cout << "Regular Grammar Rules" << endl;
    cout << "Vn = { ";
    for (auto &i : nonTerminalVariables)
    {
        cout << i << ", ";
    }
    cout << "};" << endl;
    cout << "Vt = { ";
    for (auto &i : terminalVariables)
    {
        cout << i << ", ";
    }
    cout << "};" << endl;
    cout << "Start character: " << startingCharacter << endl;
    cout << "Set of productions: P = " << endl;
    for (int i = 0; i < leftP.size(); i++)
        cout << leftP.at(i) << " -> " << rightP.at(i) << endl;
    cout << endl;
}