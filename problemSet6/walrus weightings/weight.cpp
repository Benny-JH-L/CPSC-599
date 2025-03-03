
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/egvfv7/problems/walrusweights 
Passed all cases
*/

#include<stdio.h>
#include<iostream>
#include<sstream>
#include<vector>
#include <set>
#include<algorithm>

using namespace std;

vector<int> weightSizes;

int sum(vector<int>& vec)
{
    int val = 0;
    for (int i : vec)
        val += i;
    return val;
}

// int findClosestWeight()
// {
//     int summedWeights = sum(weightSizes);
//     vector<bool> usedWeights(summedWeights, false);
//     usedWeights[0] = true;

//     for (int weight : weightSizes)
//     {
//         for (int tmp = summedWeights; tmp >= weight; tmp--)
//         {
//             if (usedWeights[tmp - weight]) {
//                 usedWeights[tmp] = true;
//                 // cout << "usedWeights["<<tmp<<"]=True"<< endl;
//             }
//         }
//     }

//     // Find the best possible weight closest to 1000, start from 1000 and count up to the first instance of `usedWeights[w]` is true
//     for (int w = 0; w <= summedWeights; ++w) {
//         if (usedWeights[w]) return w; 
//     }
// }

// int findClosestWeight() {
//     int maxWeight = sum(weightSizes);
//     vector<bool> dp(maxWeight + 1, false);
//     dp[0] = true;

//     // Update DP table
//     for (int weight : weightSizes) {
//         for (int w = maxWeight; w >= weight; --w) {
//             if (dp[w - weight]) {
//                 dp[w] = true;
//                 // cout << "dp["<<w<<"]=True"<< endl;
//             }
//         }
//     }
    
//     int closest = 0;
//     // Find the best possible weight close to 1000
//     for (int w = 0; w <= maxWeight; ++w) {
//         if (dp[w] && abs(1000-w) <= abs(1000-closest)) 
//             closest = w;  
//     }

//     return closest;
// }

int findClosestWeight() 
{

    string input;
    getline(cin, input);
    istringstream iss(input);
    int N;
    iss >> N;
    vector<bool> usedWeight;
    usedWeight.resize(2200, false);
    usedWeight[0] = true;

    for(int i = 0; i < N; i++) 
    {
        int weight;
        getline(cin, input);
        istringstream iss(input);
        iss >> weight;
        for(int w = usedWeight.size()-weight-1; w >= 0; w--) 
        {
            if(usedWeight[w]) {
                usedWeight[w+weight] = true;
            }
        }

    }

    int closest = 0;
    // Find the best possible weight close to 1000
    for (int w = 0; w <= usedWeight.size(); w++) {
        if (usedWeight[w] && abs(1000-w) <= abs(1000-closest)) 
            closest = w;  
    }
    return closest;
}


// int findClosestWeight()
// {
//     int summedWeights = sum(weightSizes);
//     set<int> usedWeights;
//     usedWeights.insert(summedWeights);

//     // Add weights to set
//     for (int& i : weightSizes)
//         usedWeights.insert(i);

//     for (int i = 0; i < weightSizes.size(); i++)
//     {
//         int weight = weightSizes[i];
//         int tmp = summedWeights;
//         // cout << "weight[i] = " << weight << "\ntmp = " << summedWeights << endl;
//         for (int j = i; j < weightSizes.size() && tmp >= weight; j++)
//         {
//             // cout << "tmp = " << tmp << " - " << weight << " = "<< tmp-weight<<endl;
//             // tmp -= weight;

//             // cout << "weightSizes[j] = " << weightSizes[j] << endl;
//             // cout << "tmp = " << tmp << " - " << weightSizes[j] << " = "<< tmp-weightSizes[j]<<endl;
//             tmp -= weightSizes[j];
//             // if (tmp >= 1000) {
//             //     usedWeights.insert(tmp);
//             //     // cout << "inserted: " << tmp << endl;
//             // }

//             usedWeights.insert(tmp);
//             // cout << "inserted: " << tmp << endl;
//         }
//     }

//     // Find the best possible weight closest to 1000
//     int closest = weightSizes[0];
//     for (int w : usedWeights)
//     {
//         if (w > closest && abs(1000-w) < abs(1000-closest)) {
//             closest = w;
//             // cout << "new cloesest = " << w << endl;
//         }
//     }
    
//     return closest;
// }


// int findClosestWeight()
// {
//     int summedWeights = sum(weightSizes);
//     set<int> usedWeights;
//     usedWeights.insert(summedWeights);

//     // Add weights to set
//     for (int& i : weightSizes)
//         usedWeights.insert(i);

//     // cout << "before sort" << endl;
//     // for (int i : weightSizes)
//     //     cout << i << endl;

//     sort(weightSizes.begin(), weightSizes.end());
//     // cout << "after sort" << endl;
//     // for (int i : weightSizes)
//     //     cout << i << endl;

//     for (int i = weightSizes.size() - 1; i >= 0; i--)
//     {
//         int tmp = summedWeights - weightSizes[i];
//         // for (int j = i; j >=0; j--)
//         for (int j = weightSizes.size() - 1; j >=0; j--)
//         {
//             if (tmp < weightSizes[j])
//                 break;
//             else if (j == i)
//                 continue;
//             usedWeights.insert(tmp - weightSizes[j]);
//             cout << "inserted: " << tmp - weightSizes[j] << endl;

//             // tmp -= weightSizes[j];

//             // if (tmp - weightSizes[j] >= 1000) {
//             //     usedWeights.insert(tmp - weightSizes[j]);
//             //     // cout << "inserted: " << tmp - weightSizes[j] << endl;
//             //     tmp -=  weightSizes[j];
//             //     // cout << "new tmp: " << tmp << endl;
//             // }
//         }
//     }

//     // Find the best possible weight closest to 1000
//     int closest = weightSizes[0];
//     for (int w : usedWeights)
//     {
//         if (w > closest && abs(1000-w) < abs(1000-closest)) {
//             closest = w;
//             // cout << "new cloesest = " << w << endl;
//         }
//     }
    
//     return closest;
// }

int main()
{
    int c = findClosestWeight();
    cout << c << endl;
    // string input;
    // getline(cin, input);
    // istringstream iss(input);
    // int N;
    // iss >> N;
    // for (int count = 0; count < N && getline(cin, input); count++)
    // {
    //     iss = istringstream(input);
    //     int i;
    //     iss >> i;
    //     weightSizes.emplace_back(i);
    // }

    // if (weightSizes.size() == 1)
    // {
    //     cout << weightSizes[0] << endl;
    // }
    // else
    // {
    //     int closest = findClosestWeight();
    //     cout << closest << endl;
    // }


    return 0;
}


        // process
        // int weight2 = process(0, weightSizes.size() - 1); 
        // int weight2 = closestWeight(weightSizes);
        // cout << weight2 << endl;
// int closestWeight(vector<int>& weights) {
//     int maxWeight = sum(weights);
    // int target = 1000;
//     vector<bool> dp(maxWeight + 1, false);
//     dp[0] = true;

//     // Update DP table
//     for (int weight : weights) {
//         for (int w = maxWeight; w >= weight; --w) {
//             if (dp[w - weight]) {
//                 dp[w] = true;
//                 cout << "dp["<<w<<"]=True"<< endl;
//             }
//         }
//     }

//     // Find the best possible weight close to 1000
//     for (int w = target; w <= maxWeight; ++w) {
//         if (dp[w]) return w;  // First achievable weight >= 1000
//     }

//     return 0; // Should not happen unless no weights are given
// }
