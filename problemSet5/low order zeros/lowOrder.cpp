
/*
https://open.kattis.com/problems/loworderzeros?tab=metadata

*/

#include<stdio.h>
#include<sstream>
#include<iostream>
#include<vector>
#include<tuple>
#include<unordered_map>
#include<cmath>

using namespace std;

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
    // for (int i = 50; i > 0; i--)
    //     cout << i<< endl;
    
    unordered_map<size_t, size_t> cache;    // key: an number (n!) to compute low order digit of, Value: the low order digit
    unordered_map<int, vector<tuple<int, int>>> primeFactorsCache;   // `key` a number to factorize, value, the prime factors

    cache[1] = 1;
    vector<string> outVec;
    string input;
    while(getline(cin, input) && input != "")
    {
        istringstream iss(input);
        size_t num;
        iss >> num;

        if (num == 0)
            break;
        else if (cache.count(num))  // check if `num`!'s low order digit has been calculated before
        {
            outVec.push_back(to_string(cache[num]));
            continue;
        }

        unordered_map<size_t, size_t> powersCounter;    // Key is base, value is exponent 
        for (size_t i = 2; i <= num; i++)
        {
            // vector<tuple<size_t, size_t>> factors;
            vector<tuple<int, int>> factors;

            primeFactorize(i, factors);
            
            for (auto pair : factors)
            {
                auto [base, pow] = pair;
                powersCounter[base] += pow;
            }
        }

        // debug
        // for (auto pair : powersCounter)
        // {
        //     auto [base, expo] = pair;
        //     cout << base << "^" << expo << endl;
        // }

        // NOT FEASABLE FOR LARGE INPUTS! (will get overflow when multiplying)
        size_t resultSoFar = 1;
        for (auto pair : powersCounter)
        {
            auto [base, expo] = pair;
            resultSoFar *= pow(base, expo);
            while (resultSoFar % 10 == 0)  // remove trailing 0s
                resultSoFar = resultSoFar / 10;
        }

        if (resultSoFar % 10 != 0)                  // remove leading digits
            resultSoFar = resultSoFar % 10;
        
        cache[num] = resultSoFar;   // add into the cache
        outVec.push_back(to_string(resultSoFar));   // add to output
    }

    // print output
    for (string s : outVec)
        cout << s << endl;
    
    return 0;
}


/*
Test cases:
3! -> 6
25! = 15511210043330985984000000 -> 4
492! = 3304..94810368000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 -> 8
49! = 608281...0240000000000

*/
        // compute the low order digit for `num`
    //     size_t resultSoFar = 1;
    //     for (size_t i = 2; i <= num; i++)
    //     {
    //         if (i == 200)
    //             int num = 1;
            
    //         resultSoFar *= i;
    //         while (resultSoFar % 10 == 0)  
    //         {
    //             resultSoFar = (resultSoFar / 10);   // remove trailing zeros
    //             // if (resultSoFar % 10 != 0)          // remove leading digits 
    //             // {
    //             //     resultSoFar = resultSoFar % 10;
    //             // }
    //         }

    //         // using 1 or the other will work for some cases but not for others...
    //         // if (to_string(resultSoFar).length() > 2) // remove leading digits
    //         // {
    //         //     resultSoFar = resultSoFar % (size_t)100;
    //         // }
    //         if (to_string(resultSoFar).length() > 3) // remove leading digits
    //         {
    //             resultSoFar = resultSoFar % (size_t)1000;
    //         }
    //         // if (to_string(resultSoFar).length() > 4) // remove leading digits
    //         // {
    //         //     // while(resultSoFar >= 10000)
    //         //     //     resultSoFar -= 10000;
    //         //     resultSoFar = resultSoFar % (size_t)10000;
    //         // }
    //         // if (to_string(resultSoFar).length() > 5) // remove leading digits
    //         // {
    //         //     // while(resultSoFar >= 10000)
    //         //     //     resultSoFar -= 10000;
    //         //     resultSoFar = resultSoFar % (size_t)100000;
    //         // }
    //     }
    //     if (resultSoFar % 10 != 0)                  // remove leading digits
    //         resultSoFar = resultSoFar % 10;

    //     cache[num] = resultSoFar;   // add into the cache
    //     outVec.push_back(to_string(resultSoFar));   // add to output
    // 
        // inside `for-loop`
        // ATTEMPT 3:
          // FAILED ON 9000!
        // size_t resultSoFar = 1;
        // for (size_t i = 2; i <= num; i++)
        // {
        //     if (i == 200)
        //         int num = 1;
            
        //     resultSoFar *= i;
        //     while (resultSoFar % 10 == 0)  
        //     {
        //         resultSoFar = (resultSoFar / 10);   // remove trailing zeros
        //         if (resultSoFar % 10 != 0)          // remove leading digits 
        //         {
        //             resultSoFar = resultSoFar % 10;
        //         }
        //     }
        // }
        // if (resultSoFar % 10 != 0)                  // remove leading digits
        //     resultSoFar = resultSoFar % 10;
        
        // Attempt 2: Failed 2nd case in submition
        // size_t resultSoFar = num;
        // for (size_t i = 2; i < num; i++)
        // {
        //     resultSoFar *= i;
        //     while (resultSoFar % 10 == 0)  
        //     {
        //         resultSoFar = (resultSoFar / 10);   // remove trailing zeros
        //         if (resultSoFar % 10 != 0)          // remove leading digits
        //         {
        //             resultSoFar = resultSoFar % 10;
        //         }
        //     }
        // }
        // if (resultSoFar % 10 != 0)                  // remove leading digits
        //     resultSoFar = resultSoFar % 10;

        // (tried to do a diff implmentation to see some diff results)
        // size_t resultSoFar = num;
        // for (size_t i = 2; i < num; i++)
        // {
        //     size_t tmp = i;
        //     // while (tmp % 10 == 0)   // remove trailing 0s
        //     //     tmp = tmp / 10;
        //     if (tmp % 10 != 0)  // remove leading digits --?
        //         tmp = tmp % 10;
        //     resultSoFar *= tmp;
        //     while (resultSoFar % 10 == 0)  
        //     {
        //         resultSoFar = (resultSoFar / 10);   // remove trailing zeros
        //         if (resultSoFar % 10 != 0)  
        //         {
        //             resultSoFar = resultSoFar % 10;
        //         }
        //     }
        // }

        // ATTTMPT 1 (DOES NOT WORK FOR ALL CASES I FOUND), and failed 2nd case in submition
        // ssize_t resultSoFar = num;
        // for (ssize_t i = num - 1; i > 0; i--)
        // {
        //     if (i == 4)
        //         int s = 2;
        //     resultSoFar *= i;
        //     ssize_t modResult = resultSoFar % 10;
        //     // if (modResult != 0)     // case 1: take the last digit (right most digit) 
        //     //     resultSoFar = modResult;    // THIS IS NOT WORKING (RUN 25! EXAMPLE)
        //     // else                    // case 2: remove the trailing 0s
        //     // {
        //         while (resultSoFar % 10 == 0)
        //             resultSoFar = (resultSoFar / 10);
        //         resultSoFar = resultSoFar % 10; // do a mod here to remove any significant digits
        //     // }
        // }
