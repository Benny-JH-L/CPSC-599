
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/j7jr2g/problems/primereduction
https://open.kattis.com/problems/primereduction?tab=metadata 

Passed All tests!
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <tuple>
#include <vector>

using namespace std;

/// @brief Calculates the prime factors of the number `n`.
/// @param n the number to be prime factored, an `long long int`.
/// @param primeFactorsOfN prime factors of `n` are put in here, a `vector<tuple<long long int, long long int>>&`.
/// `std::tuple<long long int, long long int>`: `first element` contains the `prime number` (base), `second element` contains the base's `exponent`.
void primeFactorize(long long int n, vector<tuple<long long int, long long int>>& primeFactorsOfN)
{
    // HashMap: Key is the prime factor, value at key is the exponent value
    unordered_map<long long int, long long int> primeFactorsMap;

    while (n % 2 == 0)
    {
        primeFactorsMap[2]++;
        n = n / 2;
    }

    // because 'n' is odd when entering the for-loop
    // we add 2 to i after every iteration.
    for (int i = 3; i*i <= n; i = i + 2)
    {
        while (n % i == 0)
        {
            primeFactorsMap[i]++;
            n = n / i;
        }
    }

    // convert the hashmap into a vector<tuple>
    // if (primeFactorsMap.size() == 0)    // case where `n` is prime itself
    if (n > 2)    // case where `n` is prime itself (and greater than 2)
        primeFactorsOfN.push_back(tuple(n, 1));

    for (auto pair : primeFactorsMap)
        primeFactorsOfN.push_back(tuple(pair.first, pair.second));
}

int main()
{
    string input;
    vector<string> outVec;

    while(getline(cin, input))
    {
        istringstream iss(input);
        long long int x;
        iss >> x;

        if (x == 4) // end of inputs
            break;

        int counter = 1;
        while (true)
        {
            vector<tuple<long long int, long long int>> primeFacts;
            primeFactorize(x, primeFacts);

            auto [base, expo] = primeFacts[0];

            if (primeFacts.size() == 1 && expo == 1)    // `x` is prime
            {
                outVec.push_back(to_string(x) + " " + to_string(counter));
                break;
            }

            // set `x` as the sum of its the prime factors
            x = 0;
            for (auto tup : primeFacts)
            {
                auto [base, expo] = tup;
                x += (base * expo);
            }

            counter++;
        }
    }

    for (string s : outVec)
        cout << s << endl;

    return 0;
}
