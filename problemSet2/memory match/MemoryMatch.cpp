
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <set>

using namespace std;

int main()
{
    set<int> positionsChecked;
    unordered_map<string, set<int>> map;
    string line;
    int numPairs = 0, numCards, numRounds = 1001, count = 0;
    bool gotNumCards = false, gotNumRounds = false;
    while (count < numRounds && getline(cin, line) && line != "")
    {
        if (!gotNumCards)
        {
            numCards = stoi(line);
            gotNumCards = true;
            continue;
        }
        else if (!gotNumRounds)
        {
            numRounds = stoi(line);
            gotNumRounds = true;
            continue;
        }
        
        istringstream iss(line);
        string pic1, pic2;
        int pos1, pos2;
        iss >> pos1 >> pos2 >> pic1 >> pic2;
        map[pic1].insert(pos1);
        map[pic2].insert(pos2);
        positionsChecked.insert(pos1);
        positionsChecked.insert(pos2);

        count++;
    }

    // specical case where ONLY two cards were never flipped -> can be sure they are matching??
    // numCards - positionsChecked.size() == 2 ? numPairs++ : false;
    
    for (auto mapping : map)
        mapping.second.size() == 2 ? numPairs++ : false;
    
    // Debugging
    // cout << "\nMap size (unique cards): " << map.size() << endl;
    // cout << "Count = " << count << endl;
    // cout << "pos checked = " << positionsChecked.size() << endl;
    // cout << "numCards = " << numCards << endl;
    // cout << "numRounds = " << numRounds << endl;
    // cout << "number of pairs = " << numPairs << endl;
    // cout << "Pairs: " << endl;
    // for (const auto& mapping : map)
    // {
    //     auto m2 = mapping.second;
    //     cout << "[" << mapping.first << "]: <";
    //     for (const auto i : m2)
    //         cout << i << ", ";
    //     cout << ">" << endl;
    // }
    
    cout << numPairs << endl;

    return 0;
}
