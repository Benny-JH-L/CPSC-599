
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

int N;  // degree
ssize_t M;
#define negInf -10e12

ssize_t computeRecur(ssize_t t, vector<ssize_t>& aVals, vector<signed long long>& cacheXModoMVECTOR)
{
    // cout << "welp " << t << endl; 
    if (t < cacheXModoMVECTOR.size())//cacheXModoMVECTOR[t] != negInf)        // check cache
        return cacheXModoMVECTOR[t];
    
    ssize_t sum = 0;
    // ssize_t sumNoModu = 0;
    // compute the summation (optimized): SUMM i = 2, to N. ((a_i % M) * (x_(t-i) % M)) % M
    for (int i = 1; i <= N; i++)
    {
        ssize_t xTerm = 0;
        if (t < cacheXModoMVECTOR.size()) //if (cacheXModoMVECTOR[t-i] != negInf)  // check cache
            xTerm = cacheXModoMVECTOR[t-i];
        else                        // compute the x_t-i % M value as we havent calculated it yet.
            xTerm = computeRecur(t-i, aVals, cacheXModoMVECTOR);
        
        // sumNoModu = (sumNoModu + (aVals[i]*xTerm));
        sum = (sum + ((aVals[i] % M) * xTerm) % M) % M; // Modular arithmetic at every step
    }

    ssize_t result = (aVals[0] % M + sum) % M; // x_t % M
    // cout << "x_" << t << " % "<<M<<" = " << result << endl;  // debug
    // cacheX[t] = sumNoModu;
    // cacheXModoM[t] = result;     // store the result of x_t % M
    if (t < cacheXModoMVECTOR.size())
        cacheXModoMVECTOR[t] = (result);
    else
        cacheXModoMVECTOR.emplace_back(result);
    return result;
}

ssize_t compute(ssize_t t, vector<ssize_t>& aVals, vector<signed long long>& cacheXModoMVECTOR)  
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
    return (computeRecur(t, aVals, cacheXModoMVECTOR)) % M;    // x_T % M
}

ssize_t computeIterative(ssize_t t, vector<ssize_t>& aVals, vector<signed long long>& cacheXModoMVECTOR)
{
    // Check if x_t % M has been calculated.
    if (t < cacheXModoMVECTOR.size())
        return cacheXModoMVECTOR[t];

    // bottom up iterative approach
    // calculate x_c until we finally calculate x_t
    for (ssize_t c = N; c <= t; c++)    // start c = N, because from x_0, x_1, ..., x_N are already defined
    {
        ssize_t result = 0;
        if (c < cacheXModoMVECTOR.size())
        {
            result = (result + (cacheXModoMVECTOR[c] % M)) % M;
            // cout << "x_" << c << " = " << result << endl;  // debug
            continue;
        }

        ssize_t sum = 0;
        for (int i = 1; i <= N; i++)
        {
            ssize_t xTerm = 0;
            
            if (c < cacheXModoMVECTOR.size()) 
            {
                xTerm = cacheXModoMVECTOR[c] % M;
                cout << "hey sum was usefult for x_" << c<< endl; // debug
            }
            else
                xTerm = cacheXModoMVECTOR[c-i] % M;
            
            sum = (sum + (((aVals[i] % M) * xTerm) % M)) % M; // Modular arithmetic at every step
        }
        result = ((aVals[0] % M) + sum) % M; // x_c % M
        // cacheXModoM[c] = result;
        cacheXModoMVECTOR.emplace_back(result);
        // cout << "x_" << c << " = " << result << endl;  // debug
    }
    return cacheXModoMVECTOR[t];
}

void tester(size_t T, size_t m, vector<ssize_t>& aVals, vector<signed long long>& cacheXModoMVECTOR, ssize_t expected)
{
    M = m;
    ssize_t result = compute(T, aVals, cacheXModoMVECTOR);
    cout << "x_" << T << " = " << result << " | got expected: " << (result == expected ? "True" : "False");
}
void testerIter(size_t T, size_t m, vector<ssize_t>& aVals, vector<signed long long>& cacheXModoMVECTOR, ssize_t expected)
{
    M = m;
    ssize_t result = computeIterative(T,aVals, cacheXModoMVECTOR);
    cout << "x_" << T << " % "<<M<<" = " << result << " | got expected: " << (result == expected ? "True" : "False");
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
    vector<signed long long> cacheXModoMVECTOR; // Key: int, x_0, x_1, ... x_N. Value: value of that `x_#` % M
    while (iss >> val)
    {
        // cacheXModoM[subScrpt] = val;
        // subScrpt++;
        cacheXModoMVECTOR.emplace_back(val);
    }

    // tester(6, 100000, aVals, cacheXModoMVECTOR, 8); //  for TC 1
    // tester(34683447233, 1571385, aVals, cacheXModoMVECTOR, 8); //  for TC 2
    testerIter(34683447233, 1571385, aVals, cacheXModoMVECTOR, 8); //  for TC 2


}