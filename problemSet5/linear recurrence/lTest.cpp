
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

int N;  // degree
ssize_t M;

ssize_t computeRecur(ssize_t t, vector<ssize_t>& aVals, vector<signed long long>& cacheXModoMVECTOR)
{
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
        ssize_t result = compute(T, aVals, cacheXModoMVECTOR);  // compute x_T % M
        // ssize_t result = computeIterative(T, aVals);
        cout << result << endl; // print result
        counter++;
        // cacheXModoM.clear();    // clear the cache for next computation
    }
    return 0;
}



