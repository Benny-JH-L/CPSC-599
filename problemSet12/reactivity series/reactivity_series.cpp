
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() 
{
    string input;
    int N, K;
    getline(cin, input);
    istringstream iss(input);
    iss >> N >> K;
    
    // Create adjacency list for the directed graph
    vector<vector<int>> graph(N);
    vector<int> inDegree(N, 0);
    
    // Read the experiment results
    for (int i = 0; i < K; i++) 
    {
        int a, b;
        getline(cin, input);
        iss = istringstream(input);
        iss >> a >> b;

        // a is more reactive than b
        graph[a].emplace_back(b);
        inDegree[b]++;
    }
    
    queue<int> q;
    vector<int> result;
    
    // add all vertices with in-degree 0 to the queue
    for (int i = 0; i < N; i++) 
    {
        if (inDegree[i] == 0)
            q.push(i);
    }
    
    bool unique = true;
    
    // topological order
    while (!q.empty()) 
    {
        if (q.size() > 1) 
        {
            unique = false;
            break;
        }
        
        int current = q.front();
        q.pop();
        result.emplace_back(current);
        
        for (int neighbor : graph[current]) 
        {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }
    
    // check if we have a valid topological sort containing all metals
    if (result.size() != N)
        cout << "back to the lab" << endl;
    else if (!unique)
        cout << "back to the lab" << endl; 
    else 
    {
        // print unique reactivity series
        for (int i = 0; i < N; i++) 
        {
            cout << result[i];
            if (i < N-1) cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}
