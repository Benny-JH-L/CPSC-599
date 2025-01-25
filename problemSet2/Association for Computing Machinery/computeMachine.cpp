
/*
https://open.kattis.com/problems/acm2

passed all cases.
*/

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
    // Go through input
    string firstInput, secondInput;
    int numberOfProblems = 0, indexOfFirstToSolve = -1;
    getline(cin, firstInput);
    istringstream iss(firstInput);
    iss >> numberOfProblems >> indexOfFirstToSolve;
    getline(cin, secondInput);   
    iss = istringstream(secondInput);

    int time = -1;
    vector<int> timeEstimationsVector;
    while (iss >> time) // put time estimations of each problem into a vector
    {
        timeEstimationsVector.push_back(time);
        // cout << time << endl; // debug
    }

    int numAccepted = 0, totalPenalty = 0;
    if (timeEstimationsVector[indexOfFirstToSolve] <= 300)
    {
        int totalTimePassed = timeEstimationsVector[indexOfFirstToSolve]; 
        totalPenalty = totalTimePassed;  // set the total penalty
        numAccepted++;
        timeEstimationsVector[indexOfFirstToSolve] = 1000;          // question solved, so we don't want to add it again
        sort(timeEstimationsVector.begin(), timeEstimationsVector.end());   // sort by ascending

        // calculate penalty time
        for (int i = 0; i < timeEstimationsVector.size(); i++)
        {
            if (totalTimePassed + timeEstimationsVector[i] > 300)
                break;
            
            numAccepted++;
            totalTimePassed += timeEstimationsVector[i];
            totalPenalty += totalTimePassed;
        }
    }

    cout << numAccepted << " " << totalPenalty << endl;

    return 0;
}
