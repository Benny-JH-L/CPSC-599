

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

int N;  // degree
ssize_t M;
unordered_map<int, ssize_t> cacheXModoM; // Key: int, x_0, x_1, ... x_N. Value: value of that `x_#`

// recur no work on very big stuff
ssize_t computeRecur(ssize_t t, vector<ssize_t>& aVals)
{
    ssize_t sum = 0;
    if (cacheXModoM.count(t))        // check cache
        return cacheXModoM[t];
    
    // compute the summation: SUMM i = 2, to N. a_i * x_(t-i)
    for (int i = 1; i <= N; i++)
    {
        ssize_t xTerm = 0;
        if (cacheXModoM.count(t-i))  // check cache
            xTerm = cacheXModoM[t-i];
        else                        // compute the x_t-i value as we havent calculated it yet.
            xTerm = computeRecur(t-i, aVals);
        
        sum = (sum + ((aVals[i] % M) * xTerm) % M) % M; // Modular arithmetic at every step
    }
    // ssize_t result = aVals[0] + sum;    // store x_t to the cache

    ssize_t result = (aVals[0] % M + sum) % M; // Compute x_t % M
    cacheXModoM[t] = result;     // store the result of x_t % M

    // cout << "x_" << t << " = " << result << endl;  // debug
    
    return result;
}

ssize_t compute(ssize_t t, vector<ssize_t>& aVals)
{
    return (computeRecur(t, aVals)) % M;    // x_T % M
}

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
            cout << "x_" << c << " = " << result << endl;  // debug
            continue;
        }

        ssize_t sum = 0;
        for (int i = 1; i <= N; i++)
        {
            ssize_t xTerm = 0;
            
            if (cacheXModoM.count(c)) 
                xTerm = cacheXModoM[c] % M;
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

void tester(size_t T, size_t m, vector<ssize_t>& aVals, ssize_t expected)
{
    M = m;
    ssize_t result = compute(T, aVals);
    cout << "x_" << T << " = " << result << " | got expected: " << (result == expected ? "True" : "False");
}

void testerIter(size_t T, size_t m, vector<ssize_t>& aVals, ssize_t expected)
{
    M = m;
    ssize_t result = computeIterative(T,aVals);
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
    while (iss >> val)
    {
        cacheXModoM[subScrpt] = val;
        subScrpt++;
    }
    
    // vector<ssize_t> xVals;
    // while (iss >> val)
    //     xVals.push_back(val);


    // get Q
    // getline(cin, input);
    // iss = istringstream(input);
    // int Q;
    // iss >> Q;

    // for testing purposes
    // int Q = 1; 
    // size_t T = 6;
    // size_t M = 100000;

    // size_t result =  compute(T, M, aVals);
    // cout << result << endl;

    // tester(1, 100000, aVals, 1);
    // tester(6, 100000, aVals, 8);
    testerIter(6, 100000, aVals, 8);
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

}


