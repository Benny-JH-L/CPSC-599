
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
    int numPairs = 0, numCards = 0, numRounds = 1001, count = 0;
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
        
        if (numRounds == 0 && numCards == 2)    // Case: no rounds played but there are 2 cards
        {
            numPairs++;
            break;
        }
        else if (numCards == 0) // Case: no possible pairs
            break;

        istringstream iss(line);  
        string pic1, pic2;
        int pos1, pos2;
        iss >> pos1 >> pos2 >> pic1 >> pic2;
        map[pic1].insert(pos1);
        map[pic2].insert(pos2);
        positionsChecked.insert(pos1);
        positionsChecked.insert(pos2);

        // Do not include pairs already guessed in the rounds
        if (pic1 == pic2)
        {
            map[pic1].insert(-1);  // can use map[pic2] instead.
        }
        count++;
    }
    int numDiffCardsRecorded = map.size();

    // Case where ONLY two cards were never flipped and have the same picture -> can be sure they are matching
    // if (numCards/2 - numDiffCardsRecorded == 1 && numCards - positionsChecked.size() == 2)
    //     numPairs++;
    
    // Case where we know the position of HALF of the unique cards (and their positions). 
    // for example if we know 5 unique card positions out of 10 cards, we can flip an unknown card and match it with a
    // card we flipped before.
    int numUniqueCards = numCards/2;
    if (numCards - numDiffCardsRecorded == numUniqueCards && numCards - positionsChecked.size() == numUniqueCards)
    {
        for (int count = 0; count < numUniqueCards; count++)
            numPairs++;
    }
    // Case where there are 2 positions that were never flipped and we have 2 different cards with no pairs (we can infer 2 pairs)
    int i = 0;
    for (auto mapping : map)
    {
        mapping.second.size() == 1 ? i++ : false;
    }

    if (numCards - positionsChecked.size() == 2 && i == 2)
        numPairs += 2;

    for (auto mapping : map)
        mapping.second.size() == 2 ? numPairs++ : false;
    
    // Debugging
    // cout << "\nMap size (unique cards): " << map.size() << endl;
    // cout << numCards << "/2 = " << numCards/2 << endl;
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

// Own test cases:

// 10 
// 3
// 1 2 s e
// 3 4 k o
// 5 4 j o
// expected output: 5

// 4 
// 1
// 1 2 j k
// expected output: 2