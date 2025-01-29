
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/ot4ggf/problems/tutorial

*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    string input;
    getline(cin, input);
    istringstream iss(input);
    long long int m, n, t;
    iss >> m >> n >> t;

    long long int algorithmRunTime = 1;
    vector<long long int> squares = {1, 2}; // 4, 8, 16
    vector<long long int> powers = {0, 1}; // 2, 3, 4
    bool calcTime = true;

    switch(t)
    {
        case 1: // n!                           // NEED TO USE/MAKE OWN DATA STRUCTURE AS 10^9 * 10^9 is way to big
            for (int i = n; i > 0; i--)
                algorithmRunTime *= i;

        break;
        case 2: // 2^n, ex. 2^13 = 2^8 * 2^4 * 2^1 (using repeated squareing method)
            for (long long int power = 2; true; power = power * 2)
            {
                if (power <= n)
                {
                    long long int lastSquare = squares[squares.size()-1];
                    int newSquareCalc =  lastSquare * lastSquare;
                    squares.push_back(newSquareCalc);
                    powers.push_back(power);

                    cout << "2^" << power << " = " << newSquareCalc << endl;    // debug

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
        case 3: // n^4
            for (int i = 0; i <= 3; i++)
                algorithmRunTime *= n;
            
        break;
        case 4: // n^3
            for (int i = 0; i <= 2; i++)
                algorithmRunTime *= n;
        break;
        case 5: // n^2
            algorithmRunTime = n * n;
        break;
        case 6: // n*log2(n)

        break;
        case 7: // n

        break;
    }

    if (algorithmRunTime <= m)
        cout << "AC" << endl;
    else 
        cout << "TLE" << endl;

    // debug 
    cout << "algo run time: " << algorithmRunTime << endl;

    return 0;
}
