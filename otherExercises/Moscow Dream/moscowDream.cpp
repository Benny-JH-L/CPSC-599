
/*
Question Link: https://open.kattis.com/problems/moscowdream
This passed all tests.
*/

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

int main ()
{
    string input, val;
    getline(cin, input);

    istringstream isString(input);
    vector<int> vals;
    while(isString >> val)
        vals.push_back(stoi(val));
    int a = vals[0], b = vals[1], c = vals[2], n = vals[3];

    bool printYes = true;
    if (n < 3)
        printYes = false;
    else if (a + b + c < n)
        printYes = false;
    else if (a < 1 | b < 1 | c < 1)
        printYes = false;

    cout << (printYes ? "YES" : "NO") << endl;
    
    return 0;
}
