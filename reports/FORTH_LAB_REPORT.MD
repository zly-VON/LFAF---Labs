# Chomsky Normal Form

### Course: Formal Languages & Finite Automata
### Author: Milena Cojuhari

----

## Theory
&ensp;&ensp;&ensp; A context-free grammar (CFG) is a type of formal grammar that explains a language by specifying a set of rules for building strings or sequences of symbols. Each rule in a context-free grammar is a production composed of a non-terminal symbol (also known as a variable) and a sequence of zero or more non-terminal or terminal symbols.

&ensp;&ensp;&ensp; Chomsky Normal Form (CNF) is a way to represent a context-free grammar in a specific form, where all the production rules are of the form: A → BC or A → a where A, B, and C are non-terminal symbols and a is a terminal symbol. 


## Objectives:

1. Learn about Chomsky Normal Form (CNF).
2. Get familiar with the approaches of normalizing a grammar.
3. Implement a method for normalizing an input grammar by the rules of CNF.
    1. The implementation needs to be encapsulated in a method with an appropriate signature (also ideally in an appropriate class/type).
    2. The implemented functionality needs executed and tested.
    3. A BONUS point will be given for the student who will have unit tests that validate the functionality of the project.
    4. Also, another BONUS point would be given if the student will make the aforementioned function to accept any grammar, not only the one from the student's variant.

## Implementation description

* The Chomsky Normal Form
    * This function calls all the intermediary methods to convert a CFG to CNF and prints each intermediary set of productions untill the final form.

```
void toChomskyNormalForm()
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
```

* Elimination of Epsilon/Null Productions
    * This function iterates the RHS until it finds a null production. When it finds it, it starts to iterate again through the RHS, and for every rule that contains the non-terminal variable that is null, it inserts it again by omitting the null variable.

```
void eliminateNullProductions()
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
```

* Elimination of Unit Productions
    * This function iterates the RHS until it finds a rule that contains a single non-terminal variable of the form X -> Y. When this happens, it adds new rule productions to the set for every possible replacement of Y in the existing rules.

```
void eliminateUnitProductions()
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
```

* Elimination of Useless Symbols
    * This function checks if there are any unreachable non-terminal variables by counting if they were mentioned in the RHS at least once and eliminates any rules that contain them.

```
void eliminateUselessSymbols()
{
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
                        count++;
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
}
```

* Elimination of Non-Productive Symbols
    * This function searches for non-productive symbols by checking if any non-terminal variables can derive a string of just terminal variables. When it finds a variable that cannot do it, it deletes it from the set of rules and also from all the other rules that contain that symbol.

```
void eliminateNonProductiveProductions()
{
    set<string> checked;
    set<string> nonProd;
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
                    if (islower(rhs[0])) count++;
                }
            }
            if (count == 0) nonProd.insert(leftP[i]);
        
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
}
```

* Elimination of Mixed Produtions
    * This function searches for rules that look like X -> aZ and rewrites them using new variables of the form X -> Y1Z, where Y1 -> a, and adds them to the set of productions. This process is done until all rules are of the form X -> a and X -> YZ.

```
void eliminateMixedProductions()
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
```

* Main
    * This is an example of how a grammar is initialized with an input grammar and converted to CNF.

```
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
```


## Screenshots / Results

* Variant from the register: 12

* The given grammar
    * Where 'e' represents 'epsilon'
```
Grammar Rules
Vn = { A, B, C, D, S, X, };
Vt = { a, b, };
Start character: S
Set of productions: P =
1. S -> A
2. A -> aX
3. A -> bX
4. X -> e
5. X -> BX
6. X -> b
7. B -> AD
8. D -> aD
9. D -> a
10. C -> Ca
```

* The rules of the grammar after applying the elimination of null productions
    * As we can see, the previous null production X -> e has been eliminated.
    * For the rules that contain it, like A -> aX, it was added to the set in the form A -> a.

```
Elimination of Null Productions
1. S -> A
2. A -> aX
3. A -> bX
4. X -> BX
5. X -> b
6. B -> AD
7. D -> aD
8. D -> a
9. C -> Ca
10. A -> a
11. A -> b
12. X -> B
```

* The rules of the grammar after applying the elimination of unit productions
    * All the rules in the RHS containing a single non-terminal variable were eliminated, e.g. S -> A.
    * And they were replaced with the corresponding rules for the single non-terminal variable, e.g. S -> aX, S -> a, etc.

```
Elimination of Unit Productions
1. A -> aX
2. A -> bX
3. X -> BX
4. X -> b
5. B -> AD
6. D -> aD
7. D -> a
8. C -> Ca
9. A -> a
10. A -> b
11. S -> aX
12. S -> bX
13. S -> a
14. S -> b
15. X -> AD
```

* The rules of the grammar after the elimination of useless symbols
    * The useless non-terminal variable, which is unreachable from other variables, is C, and it was eliminated.

```
Elimination of Useless Symbols
1. A -> aX
2. A -> bX
3. X -> BX
4. X -> b
5. B -> AD
6. D -> aD
7. D -> a
8. A -> a
9. A -> b
10. S -> aX
11. S -> bX
12. S -> a
13. S -> b
14. X -> AD
```

* The rules of the grammar after applying the elimination of non-productive symbols
    * The non-productive symbol is B, because it cannot generate a string of only terminal variables, and it was eliminated along with all the rules containing it.

```
Elimination of Non-Productive Symbols
1. A -> aX
2. A -> bX
3. X -> b
4. D -> aD
5. D -> a
6. A -> a
7. A -> b
8. S -> aX
9. S -> bX
10. S -> a
11. S -> b
12. X -> AD
```

* The rules of the grammar after applying the elimination of mixed symbols
* Also, the Chomsky Normal Form
    * The rules containing mixed productions were rewritten according to CNF form.
    * e.g. A -> aX was written as A -> Y1X, where Y1 -> a.

```
The Chomsky Normal Form

Grammar Rules
Vn = { A, D, S, X, Y, Y1, Y2, };
Vt = { a, b, };
Start character: S
Set of productions: P =
1. X -> b
2. D -> a
3. A -> a
4. A -> b
5. S -> a
6. S -> b
7. X -> AD
8. Y1 -> a
9. A -> Y1X
10. Y2 -> b
11. A -> Y2X
12. D -> Y1D
13. S -> Y1X
14. S -> Y2X
```


## Conclusions

&ensp;&ensp;&ensp; To accomplish this laboratory work's purpose, firstly I investigated the principles and properties of CNF, as well as its significance in context-free grammar normalization. I built a method, inside the grammar class, that takes the input grammar and applies the necessary transformations to convert it to CNF. The implemented functionality has been tested and validated manually.

&ensp;&ensp;&ensp; Finally, the laboratory work was a beneficial learning experience for catching the ideas and methodologies of grammatical normalization.