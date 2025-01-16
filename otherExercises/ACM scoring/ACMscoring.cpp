
/*
Question link: https://open.kattis.com/problems/acm
This passed all tests.
*/

#include <stdio.h>
#include <iostream>
#include <sstream>      // for 'getline(...)'
#include <vector>

using namespace std;

tuple<int, string, bool> convertToTuple(string s)
{
    string seprated;
    vector<string> elements;
    istringstream isstring(s);

    while (isstring >> seprated)
        elements.push_back(seprated);

    return make_tuple(stoi(elements[0]), elements[1], elements[2] == "right" ? true : false);
}

bool solvedAfter(string question, vector<tuple<int, string, bool>>& log)
{
    for (int i = 0; i < log.size(); i++)
    {
        auto [_, q, solved] = log[i];
        
        if (q == question && solved)
            return true;
    }

    return false;
}

int main()
{
    vector<tuple<int, string, bool>> log;

    string line;
    while (getline(cin, line) && line != "" && line != "-1")
        log.push_back(convertToTuple(line));
    
    int score = 0, numberRight = 0;

    for (int i = 0; i < log.size(); i++)
    {
        auto [time, question, solved] = log[i];

        if (solved)
        {
            score += time;
            numberRight++;
        }
        else if (solvedAfter(question, log))
            score += 20;
    }

    cout << numberRight << " " << score << endl;

    return 0;
}
