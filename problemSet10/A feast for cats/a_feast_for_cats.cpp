
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/jkrmjr/problems/cats
*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>

using namespace std;

class Graph 
{
private:
    int n;
    vector<vector<int>> adj;

public:
    Graph(int n, const vector<vector<int>>& adj) : n(n), adj(adj) {}

    string mst(int m) 
    {
        return prims(m) ? "yes" : "no";
    }

private:
    bool prims(int m) 
    {
        vector<int> best(n, 0);
        set<int> remaining;
        
        for (int i = 1; i < n; i++) 
            remaining.insert(i);
        
        vector<bool> visited(n, false);
        visited[0] = true;
        
        // min heap of pairs (weight, vertex)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        
        int edges = 0;
        int dist = 0;
        
        for (int i = 1; i < n; i++) 
        {
            heap.push({adj[0][i], i});
            best[i] = adj[0][i];
        }
        
        while (edges < n - 1) 
        {
            int w, v;
            while (true) 
            {
                if (heap.empty()) 
                    return false;   // in case the graph is not connected
                
                auto top = heap.top();
                heap.pop();
                w = top.first;
                v = top.second;
                if (!visited[v]) 
                    break;
            }
            
            edges++;
            dist += w;
            
            if (dist + n > m) 
                return false;
            
            visited[v] = true;
            remaining.erase(v);
            
            for (auto w : remaining) 
            {
                if (adj[v][w] < best[w]) 
                {
                    best[w] = adj[v][w];
                    heap.push({adj[v][w], w});
                }
            }
        }
        
        return n + dist <= m;
    }
};

void read_adj(int c, vector<vector<int>>& adj) 
{
    int edges = (c * (c - 1)) / 2;
    for (int i = 0; i < edges; ++i) 
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = w;
        adj[v][u] = w;
    }
}

void test_case(int m, int c) 
{
    vector<vector<int>> adj(c, vector<int>(c, 0));
    read_adj(c, adj);
    
    if (m < c)
        cout << "no" << endl;
    else {
        Graph g(c, adj);
        cout << g.mst(m) << endl;
    }
}

int main() 
{
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) 
    {
        int m, c;
        cin >> m >> c;
        test_case(m, c);
    }
    
    return 0;
}
