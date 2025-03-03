
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

int N;  // degree
ssize_t M;
unordered_map<int, signed long long> cacheXModoM; // Key: int, x_0, x_1, ... x_N. Value: value of that `x_#` % M
unordered_map<int, signed long long> cacheX; // Key: int, x_0, x_1, ... x_N. Value: value of that `x_#` NO MODULO

vector<signed long long> cacheXModoMVECTOR; // Key: int, x_0, x_1, ... x_N. Value: value of that `x_#` % M
#define negInf -10e12

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


// ssize_t computeRecur(ssize_t t, vector<ssize_t>& aVals)
// {
//     ssize_t sum = 0;
//     if (cacheXModoM.count(t))        // check cache
//         return cacheXModoM[t];
    
//     // compute the summation (optimized): SUMM i = 2, to N. ((a_i % M) * (x_(t-i) % M)) % M
//     for (int i = 1; i <= N; i++)
//     {
//         ssize_t xTerm = 0;
//         if (cacheXModoM.count(t-i))  // check cache
//             xTerm = cacheXModoM[t-i] % M;
//         else                        // compute the x_t-i % M value as we havent calculated it yet.
//             xTerm = computeRecur(t-i, aVals) % M;
        
//         sum = (sum + ((aVals[i] % M) * xTerm) % M) % M; // Modular arithmetic at every step
//     }

//     ssize_t result = (aVals[0] % M + sum) % M; // x_t % M
//     // cout << "x_" << t << " % "<<M<<" = " << result << endl;  // debug

//     cacheXModoM[t] = result;     // store the result of x_t % M
//     return result;
// }

// ssize_t compute(ssize_t t, vector<ssize_t>& aVals)  
// {
//     return (computeRecur(t, aVals)) % M;    // x_T % M
// }

ssize_t computeIterative(ssize_t t, vector<ssize_t>& aVals)
{
    // Check if x_t % M has been calculated.
    if (cacheXModoM.count(t)) 
        return cacheXModoM[t];

    // bottom up iterative approach
    // calculate x_c until we finally calculate x_t
    for (ssize_t c = N; c <= t; c++)    // start c = N, because from x_0, x_1, ..., x_N are already defined
    {
        ssize_t result = 0;
        if (cacheXModoM.count(c)) 
        {
            result = (result + (cacheXModoM[c] % M)) % M;
            // cout << "x_" << c << " = " << result << endl;  // debug
            continue;
        }

        ssize_t sum = 0;
        for (int i = 1; i <= N; i++)
        {
            ssize_t xTerm = 0;
            
            if (cacheXModoM.count(c)) 
            {
                xTerm = cacheXModoM[c] % M;
                cout << "hey sum was usefult for x_" << c<< endl; // debug
            }
            else
                xTerm = cacheXModoM[c-i] % M;
            
            sum = (sum + (((aVals[i] % M) * xTerm) % M)) % M; // Modular arithmetic at every step
        }
        result = ((aVals[0] % M) + sum) % M; // x_c % M
        cacheXModoM[c] = result;
        // cout << "x_" << c << " = " << result << endl;  // debug
    }
    return cacheXModoM[t];
}

// ssize_t computeRecur(ssize_t t, vector<ssize_t>& aVals)
// {
//     if (cacheXModoM.count(t))        // check cache
//         return cacheXModoM[t];
    
//     ssize_t sum = 0;
//     // ssize_t sumNoModu = 0;
//     // compute the summation (optimized): SUMM i = 2, to N. ((a_i % M) * (x_(t-i) % M)) % M
//     for (int i = 1; i <= N; i++)
//     {
//         ssize_t xTerm = 0;
//         if (cacheXModoM.count(t-i))  // check cache
//             xTerm = cacheXModoM[t-i];
//         else                        // compute the x_t-i % M value as we havent calculated it yet.
//             xTerm = computeRecur(t-i, aVals);
        
//         // sumNoModu = (sumNoModu + (aVals[i]*xTerm));
//         sum = (sum + ((aVals[i] % M) * xTerm) % M) % M; // Modular arithmetic at every step
//     }

//     ssize_t result = (aVals[0] % M + sum) % M; // x_t % M
//     // cout << "x_" << t << " % "<<M<<" = " << result << endl;  // debug
//     // cacheX[t] = sumNoModu;
//     cacheXModoM[t] = result;     // store the result of x_t % M
//     return result;
// }

ssize_t computeRecur(ssize_t t, vector<ssize_t>& aVals)
{
    if (cacheXModoMVECTOR[t] != negInf)        // check cache
        return cacheXModoMVECTOR[t];
    
    ssize_t sum = 0;
    // ssize_t sumNoModu = 0;
    // compute the summation (optimized): SUMM i = 2, to N. ((a_i % M) * (x_(t-i) % M)) % M
    for (int i = 1; i <= N; i++)
    {
        ssize_t xTerm = 0;
        if (cacheXModoMVECTOR[t-i] != negInf)  // check cache
            xTerm = cacheXModoMVECTOR[t-i];
        else                        // compute the x_t-i % M value as we havent calculated it yet.
            xTerm = computeRecur(t-i, aVals);
        
        // sumNoModu = (sumNoModu + (aVals[i]*xTerm));
        sum = (sum + ((aVals[i] % M) * xTerm) % M) % M; // Modular arithmetic at every step
    }

    ssize_t result = (aVals[0] % M + sum) % M; // x_t % M
    // cout << "x_" << t << " % "<<M<<" = " << result << endl;  // debug
    // cacheX[t] = sumNoModu;
    // cacheXModoM[t] = result;     // store the result of x_t % M
    cacheXModoMVECTOR.emplace_back(result);
    return result;
}

ssize_t compute(ssize_t t, vector<ssize_t>& aVals)  
{
    // vector<tuple<long long int, long long int>> pF;
    // primeFactorize(t, pF);
    // // use iterative to compute first `few` x_t bottom up, then finish with recursion
    // if (t % 2 == 0)
    //     // computeIterative(t / 2, aVals);
    //     cout << "hi2" << endl;
    // else if (t % 3 == 0)
    //     // computeIterative(t / 3, aVals);
    //     cout << "hi3" << endl;
    // else if (t % 5 == 0)
    //     // computeIterative(t / 5, aVals);
    //     cout << "hi5" << endl;
    // else
    // {
    //     auto& [base, _] = pF[0];
    //     computeIterative(base, aVals);
    //     cout << "hi :( , " << base << endl;
    // }

    // computeIterative(t / 100000, aVals); // compute of x_# bottom up
    return (computeRecur(t, aVals)) % M;    // x_T % M
}

int main()
{
    // get the degree
    string input;
    getline(cin, input);
    istringstream iss(input);
    iss >> N;

    ssize_t val;
    // get the N+1 integers a_0, a_1, ..., a_n
    // can range from -10^9 to 10^9 (-2^30 to 2^30).
    getline(cin, input);
    iss = istringstream(input);
    vector<ssize_t> aVals;
    while (iss >> val)
        aVals.push_back(val);

    // get the N integers x_0, x_1, ..., x_n.
    // can range from -10^9 to 10^9 (-2^30 to 2^30).
    getline(cin, input);
    iss = istringstream(input);

    int subScrpt = 0;
    // cacheXModoMVECTOR = vector<signed long long>()
    while (iss >> val)
    {
        cacheXModoM[subScrpt] = val;
        cacheXModoMVECTOR.emplace_back(val);
        subScrpt++;
    }
    
    // vector<ssize_t> xVals;
    // while (iss >> val)
    //     xVals.push_back(val);


    // get Q
    getline(cin, input);
    iss = istringstream(input);
    int Q;
    iss >> Q;

    // cout << "N: " << N << endl; // debug
    // cout << "Q: " << Q << endl; // debug

    // debug
    // cout << "a vals:" << endl;
    // for (auto& i : aVals)
    //     cout << i << " ";
    // cout << endl;
    // end debug

    // debug
    // cout << "x vals:" << endl;
    // for (const auto& pair : cacheXVals)
    //     cout << "x_" << pair.first << " = " << cacheXVals[pair.first] << endl;
    // for (auto& i : xVals)
    //     cout << i << " ";
    // cout << endl;    
    // end debug

    // get query values
    int counter = 0;
    while (counter < Q && getline(cin, input))
    {
        iss = istringstream(input);
        size_t T;   // 0 <= T <= 10^18 (2^60)
        // size_t M;   // 1 <= M <= 10^9 (2^30)
        iss >> T >> M;

        // cout << "T: " << T << "\nQ: " << Q << endl;  // debug
        ssize_t result = compute(T, aVals);  // compute x_T % M
        // ssize_t result = computeIterative(T, aVals);
        cout << result << endl; // print result
        counter++;
        // cacheXModoM.clear();    // clear the cache for next computation
    }
    return 0;
}



