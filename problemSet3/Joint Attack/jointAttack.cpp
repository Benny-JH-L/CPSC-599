
/*
https://open.kattis.com/problems/jointattack 
Passed all tests!
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <numeric> // for gcd()
#include <algorithm> // for sorting and reversing

using namespace std;

tuple<long long int, long long int> calculateRecur(vector<int>& xVals) // 1st elem: numerator, 2nd elem: denom
{
    if (xVals.size() == 1) // base case
        return tuple(1, xVals[0]);
    
    long long int wholeNum = xVals.back();
    xVals.pop_back();
    auto [numerator2, denom] = calculateRecur(xVals);

    long long int numeratorValToAdd = wholeNum * denom;
    long long int newNumerator = numerator2 + numeratorValToAdd;
    long long int GDC = gcd(newNumerator, denom);

    newNumerator = (newNumerator / GDC);
    long long int newDenom = (denom / GDC);

    // return tuple(newNumerator, newDenom);
    return tuple(newDenom, newNumerator);   // (1 / (newNumerator / newDenom) == (newDenom / newNumerator))
}

int main()
{
    string input;
    getline(cin, input);    // get n
    istringstream iss(input);
    int n;
    iss >> n;

    getline(cin, input);    // line of int's
    iss = istringstream(input);
    vector<int> xVals;

    int x;
    while (iss >> x)
        xVals.push_back(x);

    reverse(xVals.begin(), xVals.end());
    auto [numerator, denom] = calculateRecur(xVals);
    cout << denom << "/" << numerator << endl;  // yes i need to do this swap

    // TESTING
    // debug -> print what was inputted.
    // for (int v : xVals)
    //     cout << v << ", ";
    // cout << endl;

    // int popped = xVals.back();
    // xVals.pop_back();
    // cout << "popped back: " << popped << endl;
    // for (int v : xVals)
    //     cout << v << ", ";
    // cout << endl;

    // test
    // int GCDTest = gcd(13, 4);
    // cout << "gdc(13, 4) = " << GCDTest << endl;

    return 0;
}
