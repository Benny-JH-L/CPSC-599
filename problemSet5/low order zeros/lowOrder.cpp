
/*
https://open.kattis.com/problems/loworderzeros

Passed all tests!
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

long long int modPow(long long int b, long long int p, int m) 
{
    if (p == 0) 
        return 1; // base case
    long long ans = modPow(b, p/2, m);
    ans = ans*ans % m;
    if (p&1) {ans = ans*b % m;} // bitwise and
    
    return ans;
}

/// @brief Calculates the prime factors of the number `n`.
/// @param n the number to be prime factored, an `long long int`.
/// @param primeFactorsOfN prime factors of `n` are put in here, a `vector<tuple<long long int, long long int>>&`.
/// `std::tuple<long long int, long long int>`: `first element` contains the `prime number` (base), `second element` contains the base's `exponent`.
void primeFactorize(size_t n, vector<tuple<int, int>>& primeFactorsOfN)
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
    unordered_map<size_t, size_t> cache;    // key: an number (n!) to compute low order digit of, Value: the low order digit
    cache[1] = 1;
    vector<string> outVec;
    string input;
    while(getline(cin, input) && input != "")
    {
        istringstream iss(input);
        size_t n;
        iss >> n;

        if (n == 0)
            break;
        else if (cache.count(n))  // check if `num`!'s low order digit has been calculated before
        {
            outVec.push_back(to_string(cache[n]));
            // cout << cache[n] << endl;
            continue;
        }

        // compute n! while removing factors of 2 and 5 (we are essentially calculating n! using all other prime factors but those two)
        int num2s = 0;
        int num5s = 0;
        size_t result = 1;
        for (size_t i = 2; i <= n; i++) 
        {
            size_t num = i;

            // remove factors of 2 and 5 from `num`
            while(num % 2 == 0)
            {
                num = num / 2;
                num2s++;
            }
            while(num % 5 == 0)
            {
                num = num / 5;
                num5s++;
            }

            result = (result * num) % 10;    // remove leading digits (since we are removing all the 2's and 5's we won't have a trailing 0, ie have result = 0)
        }
        // take difference of powers of 2 and 5's exponents.
        int extraTwos = num2s - num5s;
        result = (result * modPow(2, extraTwos, 10)) % 10;  // account for remaining powers of 2 while removing trailing 0s.

        cache[n] = result;    // add the result to the cache
        outVec.push_back(to_string(result));

        // Works too but much faster
        // Compute the factorial's last non-zero digit
        // int result = 1;
        // int num2Divs = 0, num5Divs = 0;
        // for (int i = 2; i <= n; i++) 
        // {
        //     int num = i;
            
        //     // Remove factors of 2 and 5
        //     while (num % 2 == 0) {
        //         num2Divs++;
        //         num = num / 2;
        //     }
        //     while (num % 5 == 0) {
        //         num5Divs++;
        //         num = num / 5;
        //     }
            
        //     // Multiply remaining part
        //     if ((result * num) % 10 != 0)
        //         result = (result * num) % 10;
        // }
        
        // // Adjust for extra factors of 2 (factors of 2 will > factors 5)
        // int extraTwos = num2Divs - num5Divs;
        // // for (int i = 0; i < extraTwos; i++) {
        // //     result = (result * 2) % 10;
        // // }
        // result = (result * modPow(2, extraTwos, 10)) % 10;
        // cache[n] = result;    // add the result to the cache
        // outVec.push_back(to_string(result));

    }

    // print output
    for (string& s : outVec)
        cout << s << endl;
    
    return 0;
}

        // // WORKS TOO: (but much slower), added caching for saving prime factors for `i` but still takes too long.
        // unordered_map<int, unordered_map<int, int>> prevPrimeFactorCache; // key: prime factor of a number, value; prime factors of the number

        // unordered_map<int, int> primeFactorsOfN;    // Key is base, value is exponent 

        // // compute all the prime factors that make up of n! (should also cache these results...)
        // for (int i = 2; i <= n; i++) 
        // {
        //     // check if the prime factor of `i` has been calculated before
        //     if (prevPrimeFactorCache.count(i))
        //     {
        //         // cout << "prime factors for " << i << " have been found already!" << endl;
        //         unordered_map<int, int>& tmp = prevPrimeFactorCache[i];
        //         for (auto& tup : tmp)
        //         {
        //             auto& [base, expo] = tup;
        //             primeFactorsOfN[base] += expo;
        //         }
        //         continue;
        //     }
        //     // cout << "finding prime factors for " << i << endl;
        //     // otherwise calculate `i` prime factors
        //     vector<tuple<int, int>> primeFactors;
        //     primeFactorize(i, primeFactors);
        //     for (auto& tup : primeFactors)
        //     {
        //         auto& [base, expo] = tup;
        //         primeFactorsOfN[base] += expo;
        //         prevPrimeFactorCache[i][base] += expo;
        //     }
        // }

        // // multiply out the factorial using prime factors (excluding 2 and 5 as they will introdice trailing 0s quicker)
        // size_t result = 1;
        // for (auto& tup : primeFactorsOfN)
        // {
        //     auto& [base, expo] = tup;
        //     if (base != 2 && base != 5)
        //         result = (result * modPow(base, expo, 10)) % 10;
        // }
        // // take difference of powers of 2 and 5.
        // int num2s = primeFactorsOfN[2];
        // int num5s = primeFactorsOfN[5];
        // int extraTwos = num2s - num5s;
        // result = (result * modPow(2, extraTwos, 10)) % 10;

        // cache[n] = result;    // add the result to the cache
        // // outVec.push_back(to_string(result));
        // cout << result << endl;

// WORKS:
        // Compute the factorial's last non-zero digit
        // int result = 1;
        // int num2Divs = 0, num5Divs = 0;
        
        // for (int i = 2; i <= n; i++) 
        // {
        //     int num = i;
            
        //     // Remove factors of 2 and 5
        //     while (num % 2 == 0) {
        //         num2Divs++;
        //         num = num / 2;
        //     }
        //     while (num % 5 == 0) {
        //         num5Divs++;
        //         num = num / 5;
        //     }
            
        //     // Multiply remaining part
        //     if ((result * num) % 10 != 0)
        //         result = (result * num) % 10;
        // }
        
        // // Adjust for extra factors of 2 (factors of 2 will > factors 5)
        // int extraTwos = num2Divs - num5Divs;
        // // for (int i = 0; i < extraTwos; i++) {
        // //     result = (result * 2) % 10;
        // // }
        // result = (result * modPow(2, extraTwos, 10)) % 10;
        // cache[n] = result;    // add the result to the cache
        // outVec.push_back(to_string(result));


        // no works
        // for (int i = 2; i <= n; i++) 
        // {
        //     int tmp = i;

        //     // remove factors of 2 and 5 
        //     while (tmp % 5 == 0) {
        //         num5Divs++;
        //         tmp /= 5;
        //     }
        //     while (tmp % 2 == 0 && num5Divs > 0) {
        //         countTwo++;
        //         tmp /= 2;
        //     }
        //     if ((result * tmp) % 10 != 0 )
        //     result = (result * tmp) % 10;
        // }
        // result = (result * modPow(2, num5Divs, 10)) % 10;

        // // Compute the factorial's last non-zero digit
        // size_t result = 1;
        // int num5Divisions = 0;
        // for (size_t i = 2; i <= n; i++)
        // {
        //     size_t tmp = i;

        //     // remove factors of 5
        //     while (tmp % 5 == 0)
        //     {
        //         tmp = tmp / 5;
        //         num5Divisions++;
        //     }

        //     // remove factors of 2 that complment the 5s divided earlier.
        //     while (tmp % 2 == 0 && num5Divisions > 0)
        //     {
        //         tmp = tmp / 2;
        //         num5Divisions--;
        //     }

        //     // if ((result * tmp) % 10 != 0)
        //         result = (result * tmp) % 10;
        // }


        // for (int i = 0; i < num5Divisions; i++) {
        //     // if ((result * 5) % 10 != 0)
        //         result = (result * 5) % 10;
        // }
        // // result = (result * modPow(5, num5Divisions, 10) % 10);  // account for the remaining 5s while also removing trailing 0s.




                // // Compute the factorial's last non-zero digit
                // size_t result = 1;
                // int num5Divisions = 0;
        
                // // int tmp2 = n;
                // // while (tmp2 % 5 == 0)
                // // {
                // //     tmp2 = tmp2 / 5;
                // //     num5Divisions++;
                // // }
                // for (size_t i = 2; i <= n; i++)
                // {
                //     size_t tmp = i;
        
                //     // remove factors of 5
                //     while (tmp % 5 == 0)
                //     {
                //         tmp = tmp / 5;
                //         num5Divisions++;
                //     }
        
                //     while (tmp % 2 == 0 && num5Divisions > 0) {
                //         tmp /= 2;
                //         num5Divisions--;
                //     }
        
                //     result = (result * tmp) % 10;
                    
                //     // result = result* tmp;
                //     // while (result % 10 == 0)
                //     //     result = result / 10;
        
                //     // if ((result * tmp) % 10 != 0)
                //     //     result = (result * tmp) % 10;
                // }
        
                // // Restore remaining 5s
                // // for (int i = 0; i < num5Divisions; i++) {
                // //     result = (result * 5) % 10;
                // // }
                // // for (int i = 0; i < num5Divisions; i++) {
                // //     // if ((result * 5) % 10 != 0)
                // //         result = (result * 5) % 10;
                // // }
                // result = (result * modPow(2, num5Divisions, 10) % 10);  // account for the remaining 5s while also removing trailing 0s.
                // // result = (result * modPow(5, num5Divisions, 10) % 10);  // account for the remaining 5s while also removing trailing 0s.
                // cache[n] = result;    // add the result to the cache
                // outVec.push_back(to_string(result));

