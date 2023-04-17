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
    for (char c : rhs) 
    {
        if (isupper(c)) 
        {
            nonTerminalVariables.insert(string(1, c));
        } 
        else if (islower(c) && c != 'e') 
        {
            terminalVariables.insert(string(1, c));
        }
    }
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
    {
        cout << i + 1 << ". ";
        cout << leftP.at(i) << " -> " << rightP.at(i) << endl;
    }
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
void Grammar::printIntermediaryCNF()
{
    for (int i = 0; i < leftP.size(); i++)
    {
        cout << i + 1 << ". ";
        cout << leftP.at(i) << " -> " << rightP.at(i) << endl;
    }
}
void Grammar::toChomskyNormalForm()
{
    cout << "\n\nElimination of Null Productions" << endl;
    eliminateNullProductions();
    printIntermediaryCNF();
    cout << "\n\nElimination of Unit Productions" << endl;
    eliminateUnitProductions();
    printIntermediaryCNF();
    cout << "\n\nElimination of Useless Symbols" << endl;
    eliminateUselessSymbols();
    printIntermediaryCNF();
    cout << "\n\nElimination of Non-Productive Symbols" << endl;
    eliminateNonProductiveProductions();
    printIntermediaryCNF();
    cout << "\n\nThe Chomsky Normal Form" << endl;
    eliminateMixedProductions();
    printGrammar();
}
void Grammar::eliminateNullProductions()
{
    for (int i = 0; i < leftP.size(); i++)
    {
        if (rightP[i] == "e")
        {
            string nullS = leftP[i];
            char null = nullS[0];

            leftP.erase(leftP.begin() + i);
            rightP.erase(rightP.begin() + i);

            for (int z = 0; z < rightP.size(); z++)
            {
                string rhs = rightP[z];
                for (int j = 0; j < rhs.size(); j++)
                {
                    if (rhs[j] == null)
                    {
                        string temp = rhs;

                        temp.erase(temp.begin() + j);
                        addProduction(leftP[z], temp);
                    }
                }
            }
        }
    }
}
void Grammar::eliminateUnitProductions()
{
    for (int i = 0; i < leftP.size(); i++)
    {
        if (rightP[i].size() == 1)
        {
            string rhs = rightP[i];
            if (isupper(rhs[0]))
            {
                for (int j = 0; j < leftP.size(); j++)
                {
                    if (leftP[j] == rhs)
                    {
                        addProduction(leftP[i], rightP[j]);
                    }
                }
                leftP.erase(leftP.begin() + i);
                rightP.erase(rightP.begin() + i);
            }
        }
    }
}
void Grammar::eliminateUselessSymbols()
{
    set<string> toDelete;
    set<string> newNonTerm;
    for (auto symbol : nonTerminalVariables)
    {
        if (symbol != startingCharacter)
        {
            char var = symbol[0];
            int count = 0;
            for (int i = 0; i < leftP.size(); i++)
            {
                for (auto c : rightP[i])
                {
                    if (c == var && leftP[i] != symbol)
                    {
                        count++;
                    }
                }
            }
            if (count == 0)
            {
                for (int i = leftP.size(); i >= 0; i--)
                {
                    if (leftP[i] == symbol)
                    {
                        leftP.erase(leftP.begin() + i);
                        rightP.erase(rightP.begin() + i);
                    }
                }
                toDelete.insert(symbol);
            }
        }
    }
    for (auto symbol : nonTerminalVariables)
    {
        if (toDelete.count(symbol))
        {
            newNonTerm.insert(symbol);
        }
    }
    nonTerminalVariables = newNonTerm;
}
void Grammar::eliminateNonProductiveProductions()
{
    set<string> checked;
    set<string> nonProd;
    set<string> newNonTerm;
    for (int i = 0; i < leftP.size(); i++)
    {   
        if (!checked.count(leftP[i]))
        {
            int count = 0;
            checked.insert(leftP[i]);
            for (int j = i; j < leftP.size(); j++)
            {
                if (leftP[j] == leftP[i] && rightP[j].size() == 1)
                {
                    string rhs = rightP[j];
                    if (islower(rhs[0]))
                    {
                        count++;
                    }
                }
            }
            if (count == 0)
            {
                nonProd.insert(leftP[i]);
            }
        }
    }
    for (auto c : nonProd)
    {
        for (int i = leftP.size(); i >= 0; i--)
        {
            if (leftP[i] == c)
            {
                leftP.erase(leftP.begin() + i);
                rightP.erase(rightP.begin() + i);
            }
            else
            {
                for (auto x : rightP[i])
                {
                    char temp = c[0];
                    if (x == temp)
                    {
                        leftP.erase(leftP.begin() + i);
                        rightP.erase(rightP.begin() + i);
                    }
                }
            }
        }
    }
    for (auto symbol : nonTerminalVariables)
    {
        if (nonProd.count(symbol))
        {
            newNonTerm.insert(symbol);
        }
    }
    nonTerminalVariables = newNonTerm;
}
void Grammar::eliminateMixedProductions()
{
    int varCount = 1;
    set<string> variables;
    vector<string> newLeft;
    vector<string> newRight;

    for (int i = 0; i < leftP.size(); i++)
    {
        string l = leftP[i];
        string r = rightP[i];
        if (rightP[i].size() == 1) 
        {
            newLeft.push_back(l);
            newRight.push_back(r);
        } 
        else if ((rightP[i].size() == 2 && isupper(r[0]) && isupper(r[1])) ||
                (rightP[i].size() == 3 && isupper(r[0]) && isdigit(r[1]) && isupper(r[2]))) 
        {
            newLeft.push_back(l);
            newRight.push_back(r);
        }
        else if (rightP[i].size() == 2)
        {
            string temp;
            temp += r[0];
            if (!variables.count(temp))
            {
                string newVar = "Y" + to_string(varCount++);
                variables.insert(temp);
                addProduction(newVar, temp);
                string newSym = newVar;
                newSym += r[1];
                addProduction(l, newSym);
            }
            else 
            {
                int index = 1;
                for (auto c : variables)
                {
                    if (temp == c)
                    {
                        string newSym = "Y" + to_string(index);
                        newSym += r[1];
                        addProduction(l, newSym);
                    }
                    index++;
                }
            }
        }
    }
    leftP = newLeft;
    rightP = newRight;
}