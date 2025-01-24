
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{

    int numTestCases = 501, count = 0;
    string input;

    vector<string> outputVector;

    getline(cin, input);
    // istringstream iss(input);
    // iss >> numTestCases;
    outputVector.push_back(input);

    bool ya = true;
    while (getline(cin, input) && input != "" && ya)
    // while (getline(cin, input) && input != "" && count < numTestCases)
    {   
        outputVector.push_back(input);
        int counter = 0;
        while(counter < 9 && getline(cin, input) && input != "")
        {
            string a = input;
            a += " HELLO " + counter;
            outputVector.push_back(a);
            counter++;
        }
    }

    // cout << t;
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

