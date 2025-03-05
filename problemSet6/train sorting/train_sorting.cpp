
#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<int> cars;
vector<int> cache;  // max length train for a weighted car
int OFFSET = 100000;

void printTrain(vector<int> train)
{
    cout << "train: [";
    for (auto i : train)
        cout << i << " ";
    cout << "]"<< endl;
}

int sum(vector<int>& v)
{
    int result = 0;
    for (auto& i : v)
        result += i;
    return result;
}

int find(vector<int> train, int index)
{
    if (index >= cars.size())
        return 0;
    
    int& weight = cars[index];

    if (cache[weight] != -1)
        return cache[weight];
    else if (cache[sum(train) + OFFSET] != -1) {
        // cout << "hi";
        return cache[sum(train) + OFFSET];
    }
    else if (cache[sum(train) + OFFSET + index] != -1) {
        // cout << "hi";
        return cache[sum(train) + OFFSET + index];
    }
    if (train.size() == 0)
    {
        vector<int> copy = train;
        copy.insert(copy.begin(), cars[index]);
        // printTrain(train);
        int a = find(copy, index + 1) + 1;
        int key = sum(copy) + OFFSET;
        cache[key] = a;
        int b = find(vector<int>(), index + 1);
        cache[OFFSET + index] = b;
        int result = max(a, b);
        cache[weight] = result;

        // cache[weight] = (cache[weight] >= result ? cache[weight] : result);

        // cout << "~11~cache["<<cars[index]<< "] = " << cache[weight] << endl;

        // cout << "cache["<<cars[index]<< "] = " << cache[weight] << endl;
        return result;
    }

    // Don't use `weight`
    int a = find(train, index + 1);
    cache[sum(train) + OFFSET] = a;

    // use weight
    int b = -1;
    vector<int> copy = train;

    // cout << "Train before inserting weight: " << weight << endl;
    // printTrain(copy);

    // Case 1: add `weight` to front of the train
    if (weight < train[0])
    {
        copy.insert(copy.begin(), cars[index]);
        b = find(copy, index + 1) + 1;
    }
    // Case 2: add `weight to the end of the train
    else if (weight > train[train.size() - 1])
    {
        copy.push_back(weight);
        b = find(copy, index + 1) + 1;
    }
    cache[sum(copy) + OFFSET + index] = b;
    // cout << "Train after inserting weight: " << weight << endl;
    // printTrain(copy);

    int result = max(a, b);
    // printTrain(train);
    // cache[weight] = (cache[weight] >= result ? cache[weight] : result);
    // cout << "~~cache["<<cars[index]<< "] = " << cache[weight] << endl;
    return result;
}


// int find(int start, int end, int index)
// {
//     if (index >= cars.size())
//         return 0;
    
//     int& weight = cars[index];

//     if (cache[weight] != -1)
//         return cache[weight];

//     if (start == end)
//     {
//         // printTrain(train);
//         // cout << "~~Train start/end BEFORE adding: " << cars[start] << "-" << cars[end] << endl; 

//         int a = find(start, index, index + 1) + 1;  // use
//         int b = find(start, end, index + 1);    // dont use

//         int result = max(a, b);
//         cache[weight] = result;

//         // cache[weight] = (cache[weight] >= result ? cache[weight] : result);

//         // cout << "~11~cache["<<cars[index]<< "] = " << cache[weight] << endl;

//         // cout << "cache["<<cars[index]<< "] = " << cache[weight] << endl;
//         return result;
//     }

//     // Don't use `weight`
//     int a = find(start, end, index + 1);

//     // use weight
//     int b = -1;
//     // vector<int> copy = train;

//     // cout << "Train before inserting weight: " << weight << endl;
//     // printTrain(copy);

//     // cout << "Train start/end BEFORE adding: " << cars[start] << "-" << cars[end] << endl; 
//     // Case 1: add `weight` to front of the train
//     if (weight < cars[start])
//     {
//         // copy.insert(copy.begin(), cars[index]);
//         // cout << "1Train start/end AFTER adding: " << cars[index] << "-" << cars[end] << endl; 
//         b = find(index, end, index + 1) + 1;
//     }
//     // Case 2: add `weight to the end of the train
//     else if (weight > cars[end])
//     {
//         // copy.push_back(weight);
//         // cout << "2Train start/end AFTER adding: " << cars[start] << "-" << cars[index] << endl; 
//         b = find(start, index, index + 1) + 1;
//     }

//     // cout << "Train after inserting weight: " << weight << endl;
//     // printTrain(copy);

//     int result = max(a, b);
//     // printTrain(train);
//     // cache[weight] = (cache[weight] >= result ? cache[weight] : result);
//     // cout << "~~cache["<<cars[index]<< "] = " << cache[weight] << endl;
//     return result;
// }


int main()
{

    // for (int i = 0; i < 2000; i++)
    // {
    //     cout << i << endl;
    // }

    int N;
    cin >> N;
    
    for (int i = 0; i < N; i++) 
    {
        int w;
        cin >> w;
        cars.emplace_back(w);
    }
    // for (auto i : cars)
    //     cout << i << " ";

    cache = vector(2100 + OFFSET, -1);
    
    // for (auto i : cache)
    //     cout << i << " ";

    if (N == 0)
        cout << "0" << endl;
    else
    {
        int maxLength = find(vector<int>(), 0);
        // int maxLength = find(0, 0, 0);
        cout << maxLength << endl;
    }

    return 0;
}



// int main() {

//     int n, tt;
//     cin >> tt;

//     for (int t = 0; t < tt; t++) {
//         cin >> n;

//         int value;
//         vector<int> values, asc, desc;
//         for (int i = 0; i < n; i++) {
//             cin >> value;
//             values.push_back(value);
//             asc.push_back(1);
//             desc.push_back(1);
//         }

//         int mm = 0;
//         for (int i = asc.size() - 1; i >= 0; i--) {
//             for (int j = i + 1; j < asc.size(); j++) {
//                 if (values[i] < values[j]) {
//                     asc[i] = max(asc[i], asc[j] + 1);
//                 } else {
//                     desc[i] = max(desc[i], desc[j] + 1);
//                 }
//             }
//         }
//         for (int i = 0; i < asc.size(); i++) mm = max(mm, asc[i] + desc[i] - 1);
//         cout << mm << endl;
//     }
//     return 0;
// }


