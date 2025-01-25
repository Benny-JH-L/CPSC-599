
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <set>

using namespace std;

int main()
{
    string input;
    getline(cin, input);    // get number of cards
    istringstream iss(input);
    int numCards, numRounds;
    iss >> numCards;
    getline(cin, input);    // get number of rounds
    iss = istringstream(input);
    iss >> numRounds;

    unordered_map<string, set<int>> map;
    set<int> positionsCheckedSet;
    int numUniqueCardsRevealed = 0;

    for (int i = 0; i < numRounds && getline(cin, input) && input != ""; i++)
    {
        iss = istringstream(input);
        int pos1, pos2;
        string card1, card2;
        iss >> pos1 >> pos2 >> card1 >> card2;

        if (!map.count(card1))   // check if card1 has been revealed
            numUniqueCardsRevealed++;
    
        map[card1].insert(pos1);
        positionsCheckedSet.insert(pos1);
    
        if (!map.count(card2))   // check if card2 has been revealed
            numUniqueCardsRevealed++;

        map[card2].insert(pos2);
        positionsCheckedSet.insert(pos2);

        if (card1 == card2)     // if the 2 cards are paired don't include it in result.
            map[card1].insert(-1);

    }

    // checking cases
    int totalNumUniqueCards = numCards / 2, numCertainPairs = 0, numPositionsChecked = positionsCheckedSet.size();
    if (numCards == 2 && numRounds == 0)
        numCertainPairs++;
    else if (totalNumUniqueCards - 1 == numUniqueCardsRevealed && numCards - numPositionsChecked == 2)  // case where totalnumunqiecards - 1 are revealed and there are exactly 2 positions left unchecked
        numCertainPairs++;
    else if (totalNumUniqueCards == numUniqueCardsRevealed && numCards - numPositionsChecked == 2) // case where totalnumunqiecards are revealed and there are exactly 2 positions left unchecked where the 2 positions hold two different cards
        numCertainPairs += 2;
    else if (numUniqueCardsRevealed == totalNumUniqueCards && numPositionsChecked == totalNumUniqueCards) // case where every unique card has been revealed.
    {
        numCertainPairs += numUniqueCardsRevealed;
        for (auto mapping : map)
            mapping.second.size() == 2 ? numCertainPairs-- : false;  // if the set is of size 2 then we can make a pair, subtract so we don't double count
    }

    for (auto mapping : map)
    {
        mapping.second.size() == 2 ? numCertainPairs++ : false;     // if the set is of size 2 then we can make a pair
    }
    
    cout << numCertainPairs << endl;

    return 0;
}

think of a test case that can cover muiltiple cases
