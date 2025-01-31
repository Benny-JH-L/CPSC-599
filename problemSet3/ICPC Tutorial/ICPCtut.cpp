
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/ot4ggf/problems/tutorial
Passed all tests!
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
    double algorithmOperations = 1;

    vector<long long int> squares = {1, 2}; // 4, 8, 16
    vector<long long int> powers = {0, 1}; // 2, 3, 4
    bool calcTime = true;

    switch(t)
    {
        case 1: // n!

            if (n >= 13)    // 13! = 6227020800 (14! = 87178291200) is larger then the largest possible m value of 10^9.
            {
                cout << "TLE" << endl;
                return 0;
            }

            // Calculate n! (for n < 13)
            for (size_t i = n; i > 0; i--)
                algorithmOperations *= i;

        break;
        case 2: // 2^n

            if (n >= 30)    // 2^30 = 1073741824 which is > m's largest possible value of 10^9
            {
                cout << "TLE" << endl;
                return 0;
            }  

            // Calculate 2^n, for n < 30 using repeated squareing method ex. 2^13 = 2^8 * 2^4 * 2^1 
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
                algorithmOperations = squares[squares.size() - 1];
                calcTime = false;
            }
            // calc run time
            for (long long int index = powers.size() - 1; calcTime && index >= 0; index--)
            {
                if (powers[index] <= n)
                {
                    n -= powers[index];
                    algorithmOperations *= squares[index];
                }
            }

        break;
        case 3: // n^4

            if (n >= 178)   // 178^4 = 1003875856 > 10^9
            {
                cout << "TLE" << endl;
                return 0;
            }

            for (int i = 0; i <= 3; i++)
                algorithmOperations *= n;
            
        break;
        case 4: // n^3 

            if (n > 1000)   // 1000^3 = 10^9
            {
                cout << "TLE" << endl;
                return 0;
            }

            for (int i = 0; i <= 2; i++)
                algorithmOperations *= n;
        break;
        case 5: // n^2 

            if (n >= 31623)   // 31623^2 = 1000014129 > 10^9
            {
                cout << "TLE" << endl;
                return 0;
            }

            algorithmOperations = n * n;

        break;
        case 6: // n*log2(n)
            algorithmOperations = n * log2(n);

        break;
        case 7: // n
        
            algorithmOperations = n;
        break;
    }

    if (algorithmOperations <= m)
        cout << "AC" << endl;
    else 
        cout << "TLE" << endl;

    // debug 
    // cout << "algo run time: " << algorithmRunTime << endl;

    return 0;
}
