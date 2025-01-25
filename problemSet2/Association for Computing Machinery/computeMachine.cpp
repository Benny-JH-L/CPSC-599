
/*
https://open.kattis.com/problems/acm2
*/

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>

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
    while (iss >> time) // put times of each problem into a vector
    {
        timeEstimationsVector.push_back(time);
        cout << time << endl; // debug
    }

    int numAccepted = 0, totalPenalty = 0;
    if (timeEstimationsVector[indexOfFirstToSolve] > 300)
    {
        cout << numAccepted << " " << totalPenalty << endl;
    }
    else
    {
        totalPenalty = timeEstimationsVector[indexOfFirstToSolve];  // set the total penalty
        timeEstimationsVector[indexOfFirstToSolve] = 999;           // question solved, so we don't want to add it again
        // calculate penalty time
        for (int i = 0; i < timeEstimationsVector.size(); i++)
        {
            // find the min value in vector, then add it to penalty
        }
    }

    return 0;
}
