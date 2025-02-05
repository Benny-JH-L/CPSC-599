
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/j7jr2g/problems/primesieve
https://open.kattis.com/problems/primesieve?tab=metadata 
Passed All Tests!
*/

#include<stdio.h>
#include<sstream>
#include<iostream>
#include<unordered_map>
#include<tuple>
#include<vector>

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

/// @brief Finds all the prime numbers that are <= `n` and puts them into the `vector<long long int>& primesLessThanN` (this vector will be cleared before computation).
/// if `n` is 1, return's 0.
/// Run time of `O(sqrt(n) * log(log (n)))`.
/// @param n a `const long long int&`.
/// @return the number of primes that are <= `n`, a `long long int`.
long long int SieveOfEratosthenes(const long long int& n)
{
    if (n == 1)
        return 0;

    // This vector<bool> will store which numbers are prime, 
    // if it is true at index `i` then `i` is a prime number
    // initialize vector<bool> from [0..n] to true
    vector<bool> primes(n + 1, true);

    // Find the prime numbers <= `n`
    for (int i = 2; i * i <= n; i++)
    {
        // check if `true`, if so then `i` is prime and
        // remove all numbers that are divisible by `i`
        if (primes[i])  
        {
            // start removing at i^2, then continue by adding `i` to itself (`r` will be powers of `i`)
            for (int r = i * i; r <= n; r += i) 
                primes[r] = false;              // set false to remove
        }
    }

    // Send back the primes less than `n`
    long long int c = 0;
    for (int p = 2; p <= n; p++)
    {
        if (primes[p])
            c++;
    }
    return c;
}

int main()
{
    string input;

    getline(cin, input);
    istringstream iss(input);
    long long int n;
    int q;
    iss >> n >> q;

    vector<string> outVec;

    // number of primes <= `n` is calculated later

    int counter = 0;
    unordered_map<long long int, string> computedResultsMap;

    while(counter < q && getline(cin, input))
    {
        iss = istringstream(input);
        long long int x;
        iss >> x;

        if (x == 1) // special case, due to how my `primeFactorize(n)` deals with input as primes (returns `n`)
            outVec.push_back("0");
        else
        {

            // helps with optimizing, although not really used
            // if (computedResultsMap.count(x))
            // {
            //     // cout << "hey :)" << endl; // debug
            //     // outVec.push_back("hey :)"); // debug
            //     outVec.push_back(computedResultsMap[x]);
            //     continue;
            // }

            vector<tuple<long long int, long long int>> primeFactorsOfX;
            primeFactorize(x, primeFactorsOfX);
            auto [base, expo] = primeFactorsOfX[0];

            if (primeFactorsOfX.size() == 1 && expo == 1)    // `x` is a prime number (factors of prime number will be itself, x^1 or 1, tho i don't include 1)
                outVec.push_back("1");
            else                                // `x` is not a prime number
                outVec.push_back("0");
            
            computedResultsMap[x] = outVec[outVec.size() - 1];
        }

        counter++;
    }

    // calc number of primes <= `n`
    // cout << "CALC-ing sieve" << endl; // debug
    cout << SieveOfEratosthenes(n) << endl;

    // print results
    for (string s : outVec)
        cout << s << endl;

    return 0;
}
