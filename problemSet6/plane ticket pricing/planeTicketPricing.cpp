#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, W;
vector<vector<int>> prices;
vector<vector<int>> sold;

int dp(int index, int remaining)
{
    if (index == W + 1):
        return 0;
    
    int result = 0;
    vector<int> price = prices[index];
    vector<int> s = sold[index];
    
    for ()
}

int main()
{
    string input;
    getline(cin, input);
    istringstream iss(input);
    iss >> N >> W;

    while(W + 1 > 0 && getline(cin, input))
    {
        iss = istringstream(input);
        int num;
        vector<int> lineValues;
        for (iss >> num)
            lineValues.emplace_back(num);
        lineValues.erase(lineValues.begin());   // remove 1st element
        vector<int> tmp;
        for (int i = 0; i < lineValues.size() / 2; i++)
            tmp.emplace_back(lineValues[i]);
        vector<int> tmp2;
        for  (int i = lineValues.size() / 2; i < lineValues.size(); i++)
            tmp2.emplace_back(lineValues[i]);
        
        prices.emplace_back(tmp);
        sold.emplace_back(tmp2);
        W--;
    }

    profit = 

    return 0;
}

// typedef vector<int> vi;
// typedef vector<vector<int>> vvi;

// void maximize_revenue(int N, int W, vector<vector<int>>& price_data) {
//     vvi dp(W + 1, vi(N + 1, 0));
//     vvi choice(W + 1, vi(N + 1, 0));
    
//     for (int week = W - 1; week >= 0; --week) {
//         int K = price_data[week][0];
//         vi prices(price_data[week].begin() + 1, price_data[week].begin() + 1 + K);
//         vi sales(price_data[week].begin() + 1 + K, price_data[week].end());
        
//         for (int seats_left = 0; seats_left <= N; ++seats_left) {
//             int best_revenue = 0, best_price = 0;
            
//             for (int i = 0; i < K; ++i) {
//                 int price = prices[i];
//                 int sell = min(sales[i], seats_left);
//                 int revenue = price * sell + dp[week + 1][seats_left - sell];
                
//                 if (revenue > best_revenue || (revenue == best_revenue && price < best_price)) {
//                     best_revenue = revenue;
//                     best_price = price;
//                 }
//             }
            
//             dp[week][seats_left] = best_revenue;
//             choice[week][seats_left] = best_price;
//         }
//     }
    
//     cout << dp[0][N] << endl;
//     cout << choice[0][N] << endl;
// }

// int main() {
//     int N, W;
//     cin >> N >> W;
//     vector<vector<int>> price_data(W);
    
//     for (int i = 0; i < W; ++i) {
//         int K;
//         cin >> K;
//         price_data[i].resize(2 * K + 1);
//         price_data[i][0] = K;
        
//         for (int j = 1; j <= 2 * K; ++j) {
//             cin >> price_data[i][j];
//         }
//     }
    
//     maximize_revenue(N, W, price_data);
//     return 0;
// }
