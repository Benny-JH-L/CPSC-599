
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/jkrmjr/problems/redbluetree
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class DisjointSet 
{
private:
    int* parent;
    int* rank;

public:
    DisjointSet(int n) 
    {
        parent = new int[n];
        rank = new int[n]();  // Initialize to zero

        for (int i = 1; i <= n; i++) 
            parent[i] = i;
    }

    ~DisjointSet() 
    {
        delete[] parent;
        delete[] rank;
    }

    // Find with path compression
    int find(int x) 
    {
        int root = x;
        
        // Find the root
        while (parent[root] != root) 
            root = parent[root];
        
        // Compress path
        while (parent[x] != root) 
        {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        
        return root;
    }

    // Union by rank
    bool unionSets(int x, int y) 
    {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) 
            return false;

        if (rank[root_x] < rank[root_y]) 
            parent[root_x] = root_y;
        else 
        {
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) 
                rank[root_x]++;
        }
        return true;
    }

    // Check if two elements are in the same set
    bool sameSet(int x, int y) 
    {
        return find(x) == find(y);
    }
};

bool canFormSpanningTree(int n, vector<pair<char, pair<int, int>>>& edges, int k) 
{
    int m = edges.size();
    
    for (int blueMask = 0; blueMask < (1 << m); blueMask++) 
    {
        int blueCount = 0;
        DisjointSet dsu(n);
        
        for (int i = 0; i < m; i++) 
        {
            if (blueMask & (1 << i)) 
            {
                if (edges[i].first != 'B') 
                    continue;
                
                blueCount++;
                if (!dsu.unionSets(edges[i].second.first, edges[i].second.second))
                    blueCount--;
            }
        }
        
        // Second pass: Add red edges to complete spanning tree
        for (int i = 0; i < m; i++) 
        {
            if (!(blueMask & (1 << i))) 
            {
                if (edges[i].first != 'R') continue;
                
                // if (!dsu.unionSets(edges[i].second.first, edges[i].second.second)) {
                // }
            }
        }
        
        int components = 0;
        for (int i = 1; i <= n; i++) 
        {
            if (dsu.find(i) == i) 
                components++;
        }
        
        if (components == 1 && blueCount == k) 
            return true;
    }
    
    return false;
}

int main() 
{
    string input;
    getline(cin, input);
    int n, m, k;
    istringstream iss(input);
    iss >> n >> m >> k;
    
    vector<pair<char, pair<int, int>>> edges(m);
    
    for (int i = 0; i < m && getline(cin, input); i++) 
    {
        char color;
        int from, to;
        iss = istringstream(input);
        iss >> color >> from >> to;
        edges[i] = {color, {from, to}};
    }
    
    cout << (canFormSpanningTree(n, edges, k) ? 1 : 0) << endl;
    
    return 0;
}
