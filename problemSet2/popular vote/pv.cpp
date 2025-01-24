
/*
https://open.kattis.com/problems/vote
Passed all cases :)
*/

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{

    int numTestCases = 501, count = 0;
    string input;

    getline(cin, input);
    istringstream iss(input);
    iss >> numTestCases;
    vector<string> outputVector;

    while (count < numTestCases && getline(cin, input) && input != "")
    {   
        iss = istringstream(input);
        int count2 = 0, numCandidates, totalVotes = 0;
        iss >> numCandidates;
        vector<int> candidateVotesVector;

        while(count2 < numCandidates && getline(cin, input) && input != "") // go through candidates votes
        {
            iss = istringstream(input);
            int currentCandidateVotes;
            iss >> currentCandidateVotes;
            candidateVotesVector.push_back(currentCandidateVotes);
            totalVotes += currentCandidateVotes;
            count2++;
        }

        // figure out potential winner of this test case

            // get max vote count inside vector.
            // then check if the max vote count happens more than once if so -> no winner.
            // if max vote count happens once then check are they minority of majority winner:
                // majority: vote count > (total votes / 2.f)
                // minority: otherwise
        int highestVoteCount = 0, indexForHighestVoteCount = 0;
        for (int i = 0; i < candidateVotesVector.size(); i++)
        {
            if (candidateVotesVector[i] > highestVoteCount)
            {
                indexForHighestVoteCount = i;
                highestVoteCount = candidateVotesVector[i];
            }
            // cout << "index " << i << ": " << candidateVotesVector[i] << endl;   // debug
        }
        
        int numTimesHighestVoteOccures = 0;
        for (int v : candidateVotesVector)
            v == highestVoteCount ? numTimesHighestVoteOccures++ : false;
        
        string winnerType = "";
        if (numTimesHighestVoteOccures > 1)
            outputVector.push_back("no winner");
        else if ((float)highestVoteCount > (totalVotes / 2.f))
            outputVector.push_back(("majority winner " + to_string(indexForHighestVoteCount + 1)));
        else 
            outputVector.push_back(("minority winner " + to_string(indexForHighestVoteCount + 1)));
        
        count++;
    }

    for (string outLine : outputVector)
        cout << outLine << endl;
    
    return 0;
}

// test case:
// 2
// 3
// 10
// 21
// 10
// 2
// 30
// 40

