
#include <stdio.h> 
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

using namespace std;

// Function to count islands in a given sequence
int find(vector<int>& v, int index)
{
    int sum = 0;
    for (int i = 1; i < v.size() - index; i++)
    {
        int max_b = max(v[i-1], v[i+index]);
        int min = *min_element(v.begin() + i, v.begin() + i + index);

        if (max_b < min)
            sum += 1;
    }
    return sum;
}

int findIslands(vector<int>& v)
{
    int sum = 0;
    for (int i = 1; i < 11; i++)
        sum += find(v, i);
    return sum;
}


int main() 
{
    string line;
    int P;
    getline(cin, line);
    istringstream iss(line);
    iss >> P;

    for (int i = 0; i < P && getline(cin, line); i++) 
    {        
        vector<int> numbers;
        iss = istringstream(line);
        int num;
        while (iss >> num) 
            numbers.push_back(num);
        
        cout << (i + 1) << " " << findIslands(numbers) << std::endl;
    }

    return 0;
}
