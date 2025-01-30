
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/ot4ggf/problems/tutorial

*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

#include <unordered_map>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    string input;
    getline(cin, input);
    istringstream iss(input);
    // unsigned long long int m, n, t;
    int m, n;
    int t;
    iss >> m >> n >> t;

    // unsigned long long int algorithmRunTime = 1;
    double algorithmRunTime = 1;

    vector<long long int> squares = {1, 2}; // 4, 8, 16
    vector<long long int> powers = {0, 1}; // 2, 3, 4
    bool calcTime = true;

    switch(t)
    {
        case 1: // n!

            if (n >= 14)    // 14! is larger then the largest m value.
                cout << "TLE" << endl;
            else 
                cout << "AC" << endl;

            // return 0;
            // for (size_t i = n; i > 0; i--)
            //     algorithmRunTime *= i;

        break;
        case 2: // 2^n, ex. 2^13 = 2^8 * 2^4 * 2^1 (using repeated squareing method)

            if (n >= 30)
            {
                cout << "TLE" << endl;
                return;
            }  

            for (long long int power = 2; true; power = power * 2)
            {
                if (power <= n)
                {
                    long long int lastSquare = squares[squares.size()-1];
                    int newSquareCalc =  lastSquare * lastSquare;
                    squares.push_back(newSquareCalc);
                    powers.push_back(power);

                    // cout << "2^" << power << " = " << newSquareCalc << endl;    // debug

                    if (power == n)
                        break;
                }
                else
                    break;
            }
            
            if (powers[powers.size() - 1] == n)
            {
                algorithmRunTime = squares[squares.size() - 1];
                calcTime = false;
            }
            // calc run time
            for (long long int index = powers.size() - 1; calcTime && index >= 0; index--)
            {
                if (powers[index] <= n)
                {
                    n -= powers[index];
                    algorithmRunTime *= squares[index];
                }
            }

        break;
        case 3: // n^4      // find the number 'n' such that n^4 >= 10^9 
            for (int i = 0; i <= 3; i++)
                algorithmRunTime *= n;
            
        break;
        case 4: // n^3 // find the number 'n' such that n^3 >= 10^9 
            for (int i = 0; i <= 2; i++)
                algorithmRunTime *= n;
        break;
        case 5: // n^2 // find the number 'n' such that n^2 >= 10^9 
            algorithmRunTime = n * n;
        break;
        case 6: // n*log2(n)
            algorithmRunTime = n * log2(n);
        break;
        case 7: // n
            algorithmRunTime = n;
        break;
    }

    if (algorithmRunTime <= m)
        cout << "AC" << endl;
    else 
        cout << "TLE" << endl;

    // debug 
    // cout << "algo run time: " << algorithmRunTime << endl;

    return 0;
}
