
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/som8q2/problems/drivinglanes

*/

#include <bits/stdc++.h>

using namespace std;

const ssize_t N = 252, inf = 10e8;

ssize_t minDist[N][N];
ssize_t len[N];
ssize_t S[N], C[N];

ssize_t cache[N][N];
ssize_t straight[N];
ssize_t length[N];

int main()
{
    ssize_t n, m;
    ssize_t k, r;
    cin >> n >> m >> k >> r;
    for(ssize_t i = 1; i <= n; ++i) {
        cin >> len[i];
    }
    for(ssize_t i = 1; i <= n-1; ++i) {
        cin >> S[i] >> C[i];
    }
    for(ssize_t i = 0; i <= n; ++i) {//for each seg
        for(ssize_t j = 0; j <= m; ++j) {//for each lane
            minDist[i][j] = inf;
        }
    }

    // cout << "C[]:";
    // for (int& i : C)
    //     cout << i << " ";

    // cout << "\nS[]:";
    // for (int& i : S)
    //     cout << i << " ";
    // cout << endl;

    minDist[0][1] = 0;
    for(ssize_t i = 1; i <= n; ++i)  //for each seg
    {
        for(ssize_t j = 1; j <= m; ++j)  //for each lane
        {
            ssize_t maxLaneChanges = len[i]/k;
            for(ssize_t k = max(ssize_t(1), j-maxLaneChanges); k <= min(m, j+maxLaneChanges); ++k) 
            {
                ssize_t laneChanges = abs(k-j);
                ssize_t distCurve = 0;
                if(i > 1) 
                    distCurve = S[i-1] + C[i-1]*k;
                minDist[i][j] = min(minDist[i][j], laneChanges*(k+r) + len[i]-laneChanges*k + distCurve + minDist[i-1][k]);
            }
        }
    }
    cout << minDist[n][1] << endl;;
    return 0;
}
