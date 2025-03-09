/*
https://open.kattis.com/problems/uxuhulvoting?tab=metadata

*/

#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <climits>

using namespace std;

vector<string> states = {"NNN", "NNY", "NYN", "NYY", "YNN", "YNY", "YYN", "YYY"};

string determineOutcome(int m, vector<vector<int>>& preferences) 
{
    // convert state strings to indices
    map<string, int> stateToIndex;
    for (int i = 0; i < states.size(); i++) 
        stateToIndex[states[i]] = i;
    
    // initialize the final outcome for each state
    vector<string> finalOutcome(8, "");
    
    // start from the last priest and move backwards
    for (int priest = m - 1; priest >= 0; priest--) 
    {
        vector<int> currentPreferences = preferences[priest];
        vector<string> newFinalOutcome(8, "");
        
        for (int indexState = 0; indexState < 8; indexState++) 
        {
            string currState = states[indexState];
            string bestOutcome = "";
            int bestPreference = INT_MAX;
            
            // try flipping each stone
            for (int flip = 0; flip < 3; flip++) 
            {
                string newState = currState;
                newState[flip] = (newState[flip] == 'N') ? 'Y' : 'N';
                
                int indexNewState = stateToIndex[newState];
                
                // get the outcome after this flip
                string outcome = (priest != m - 1) ? finalOutcome[indexNewState] : newState;
                int preference = currentPreferences[stateToIndex[outcome]];
                
                if (preference < bestPreference) 
                {
                    bestPreference = preference;
                    bestOutcome = outcome;
                }
            }
            
            newFinalOutcome[indexState] = bestOutcome;
        }
        
        finalOutcome = newFinalOutcome;
    }

    return finalOutcome[stateToIndex["NNN"]];
}

int main() 
{
    int n;
    cin >> n;
    
    for (int round = 0, m; round < n; round++) 
    {
        cin >> m;
        vector<vector<int>> preferences(m, vector<int>(8));
        
        for (int priest = 0; priest < m; priest++)
         {
            for (int i = 0; i < 8; i++) 
                cin >> preferences[priest][i];
        }

        string outcome = determineOutcome(m, preferences);
        cout << outcome << endl;
    }
    
    return 0;
}


