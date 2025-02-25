
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

int N;  // degree
unordered_map<int, ssize_t> cache; // Key: int, x_0, x_1, ... x_N. Value: value of that `x_#`

ssize_t computeRecur(ssize_t t, vector<ssize_t>& aVals, vector<ssize_t>& xVals)
{
    ssize_t sum = 0;
    for (int i = 1; i < N; i++)
    {
        // check cache here----

        sum += aVals[i]*computeRecur(t-i, aVals, xVals);
    }
    return sum;
}

ssize_t compute(ssize_t t, vector<ssize_t>& aVals, vector<ssize_t>& xVals)
{
    // int i = 1;
    return aVals[0] + computeRecur(t, aVals, xVals);
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
    vector<ssize_t> xVals;
    while (iss >> val)
        xVals.push_back(val);

    // get Q
    getline(cin, input);
    iss = istringstream(input);
    int Q;
    iss >> Q;

    cout << "N: " << N << endl; // debug
    cout << "Q: " << Q << endl; // debug

    // debug
    cout << "a vals:" << endl;
    for (auto& i : aVals)
        cout << i << " ";
    cout << endl;
    // end debu

    // debug
    cout << "x vals:" << endl;
    for (auto& i : xVals)
        cout << i << " ";
    cout << endl;    
    // end debug

    // get query values
    int counter = 0;
    while (counter < Q && getline(cin, input))
    {
        iss = istringstream(input);
        size_t T;   // 0 <= T <= 10^18 (2^60)
        size_t M;   // 1 <= M <= 10^9 (2^30)
        iss >> T >> M;

        cout << "T: " << T << "\nQ: " << Q << endl;  // debug

        counter++;
    }
    return 0;
}

