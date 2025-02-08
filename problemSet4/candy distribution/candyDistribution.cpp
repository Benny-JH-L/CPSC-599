
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/j7jr2g/problems/candydistribution
https://open.kattis.com/problems/candydistribution?tab=metadata 

*/

#include<stdio.h>
#include<iostream>
#include<sstream>

#include<cmath>
#include<vector>
#include<tuple>
#include<unordered_map>
#include<numeric>

using namespace std;

/// @brief Calculates the prime factors of the number `n`.
/// @param n the number to be prime factored, an `long long int`.
/// @param primeFactorsOfN prime factors of `n` are put in here, a `vector<tuple<long long int, long long int>>&`.
/// `std::tuple<long long int, long long int>`: `first element` contains the `prime number` (base), `second element` contains the base's `exponent`.
void primeFactorize(size_t n, vector<tuple<long long int, long long int>>& primeFactorsOfN)
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

// specifies the number of integers less than N that are relatively prime to N

/// @brief Computes the number of integers that are less than `n` that are relatively prime to `n`.
/// Relatively prime is if the gcd(`n`, #) = 1.
/// @param n a `long long int`.
/// @return the number of integers that are less than `n` that are relatively prime to `n`, a `long long int`.
long long int eulerTotient(long long int n)
{
    vector<tuple<long long int, long long int>> primeFactors;
    primeFactorize(n, primeFactors);

    unsigned long long int numerator = 1;
    unsigned long long int denominator = 1;

    // Compute Capital PI (products) from (prime factors, p, of N) (1 - 1/(p)).
    for (size_t i = 0; i < primeFactors.size(); i++)   
    {
        auto [base, _] = primeFactors[i];
        numerator *= (base - 1);    // result of 1 - (1/`base`) with the previous calcualted numerator
        denominator *= base;        // multiplying the denominator with `base` 

        unsigned long long int GCD = gcd(numerator, denominator); // reduce fraction
        numerator = numerator / GCD;
        denominator = denominator / GCD;
    }

    numerator *= n;    // multiply by `n` last
    unsigned long long int GCD = gcd(numerator, denominator); // reduce fraction
    numerator = numerator / GCD;
    denominator = denominator / GCD;
    return (numerator / denominator);   // return the result.
}


long long int modPow(long long int b, long long int p, int m) 
{
    if (p == 0) 
        return 1; // base case
    long long ans = modPow(b, p/2, m);
    ans = ans*ans % m;
    if (p&1) {ans = ans*b % m;} // bitwise and
    
    return ans;
}

/// @brief Computes and return the modular inverse `x`, if and only if `a` and `modVal` are relatively prime (gcd(`a`, `modVal`) == 1), such that: `a * x % modVal` = `remainderVal` % `modVal`.
/// Example. Let `a` = 7, `modVal` = 10, and `remainderVal` = 1, then the computed value of `x` will be 3. 
/// Check, (7 * 3) % 10 == 1 % 10 => 21 % 10 == 1 % 10 => 1 % 10 == 1 % 10, thus, `x` = 3.
/// @param a a coefficient, `size_t`.
/// @param remainderVal the remainder of the modular, `size_t`.
/// @param modVal the modular value, `size_t`.
/// @return a `long long int`, `return's -1 if modular inverse is not possible`.
long long int modularInverse(size_t a, size_t remainderVal, size_t modVal)
{
    if (gcd(a, modVal) != 1)    // check if `a` and `modVal` are relatively prime to each other
        return -1;              // modular inverse is not possible, return -1
    size_t eulerTotientofA = eulerTotient(modVal);  // compute phi(`modVal`)
    size_t aInverse = modPow(a, eulerTotientofA - 1, modVal);   // `aInverse` = a^(phi(`modVal`) - 1) mod `modVal`
    return (remainderVal * aInverse); //% modVal;                  // reduce modular-inverse `x` value by modular of `modVal`.
}

int main()
{
    string input;
    getline(cin, input);
    istringstream iss(input);
    int numTests;
    iss >> numTests;
    vector<string> outVec;

    for (int i = 0; i < numTests && getline(cin, input) && input != ""; i++)
    {
        iss = istringstream(input);
        size_t modVal, a;
        iss >> modVal >> a;
        long long int x = modularInverse(a, 1, modVal);
        if (x == -1 || (a == modVal)) // number of children == number of candies per bag -> impossible, or x == -1
            outVec.push_back("IMPOSSIBLE");
        else
            outVec.push_back(to_string(x));
    }

    for (string s : outVec)
        cout << s << endl;

    return 0;
}
// 2^30 = 1073741824
// phi(1073741824) = 536870912

