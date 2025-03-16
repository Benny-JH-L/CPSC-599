
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <stack>

using namespace std;

// evaluate a WFF given the variable truth assignments
bool evaluateWFF(string& formula, map<char, bool>& values) 
{
    stack<bool> stack;
    
    // process the formula from right to left (postfix notation)
    for (int i = formula.length() - 1; i >= 0; i--) 
    {
        char c = formula[i];
        
        if (c >= 'p' && c <= 't') 
        {
            // variables - push their values onto the stack
            auto it = values.find(c);
            if (it != values.end()) 
                stack.push(it->second);
            else 
                stack.push(false); // default value if variable not found
        } 
        else if (c == 'N') 
        {
            // NOT operation
            bool operand = stack.top();
            stack.pop();
            stack.push(!operand);
        } 
        else if (c == 'K' || c == 'A' || c == 'C' || c == 'E') 
        {
            bool x = stack.top(); 
            stack.pop();
            bool w = stack.top(); 
            stack.pop();
            
            if (c == 'K')       // AND
                stack.push(w && x);
            else if (c == 'A')  // OR
                stack.push(w || x);
            else if (c == 'C')  // IMPLIES
                stack.push(!w || x);
            else if (c == 'E')  // EQUALS
                stack.push(w == x);
        }
    }
    
    return stack.top();
}

// check if a WFF is a tautology
bool isTautology(string& formula) 
{
    // find all variables in the formula
    set<char> variables;
    for (char c : formula) 
    {
        if (c >= 'p' && c <= 't') 
            variables.insert(c);
    }
    
    // convert set to vector for easier indexing
    vector<char> vars(variables.begin(), variables.end());
    int numVars = vars.size();
    
    // try all possible variable assignments
    for (int i = 0; i < (1 << numVars); i++) 
    {
        map<char, bool> values;
        
        // assign truth values based on bits in i
        for (int j = 0; j < numVars; j++) 
            values[vars[j]] = (i & (1 << j)) != 0;
        
        // if the formula evaluates to false for any assignment, it's not a tautology
        if (!evaluateWFF(formula, values)) 
            return false;
    }
    
    // if we get here, the formula evaluated to true for all assignments
    return true;
}

int main() 
{
    string formula;
    
    while (getline(cin, formula) && formula != "0") 
    {    
        string result;
        isTautology(formula) ? result = "tautology" : result = "not";
        cout << result << endl;
    }
    
    return 0;
}

