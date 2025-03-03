#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int N, W;
    cin >> N >> W;

    vector<vector<pair<vector<int>, vector<int>>>> estimates(W + 1);

    for (int w = 0; w <= W; ++w) {
        int K;
        cin >> K;
        vector<int> prices(K);
        vector<int> seats(K);

        for (int i = 0; i < K; ++i) {
            cin >> prices[i];
        }
        for (int i = 0; i < K; ++i) {
            cin >> seats[i];
        }

        estimates[w] = make_pair(prices, seats);
    }

    vector<vector<int>> dp(W + 1, vector<int>(N + 1, -1));

    for (int s = 0; s <= N; ++s) {
        dp[0][s] = 0;
    }

    for (int w = 1; w <= W; ++w) {
        auto& prices = estimates[W - w].first;
        auto& seats = estimates[W - w].second;

        for (int s = 0; s <= N; ++s) {
            int maxRevenue = -1;
            for (size_t i = 0; i < prices.size(); ++i) {
                int p = prices[i];
                int sold = min(s, seats[i]);
                int revenue = p * sold + dp[w - 1][s - sold];
                if (revenue > maxRevenue) {
                    maxRevenue = revenue;
                }
            }
            dp[w][s] = maxRevenue;
        }
    }

    int maxTotalRevenue = dp[W][N];

    int currentPrice = 0;
    int s = N;
    for (int w = W; w > 0; --w) {
        auto& prices = estimates[W - w].first;
        auto& seats = estimates[W - w].second;

        for (size_t i = 0; i < prices.size(); ++i) {
            int p = prices[i];
            int sold = min(s, seats[i]);
            if (dp[w][s] == p * sold + dp[w - 1][s - sold]) {
                currentPrice = p;
                s -= sold;
                break;
            }
        }
    }

    cout << maxTotalRevenue << endl;
    cout << currentPrice << endl;

    return 0;
}
