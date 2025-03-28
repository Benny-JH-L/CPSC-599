
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class DisjointSet 
{
    private:
        vector<int> parent, rank;
    
    public:
        DisjointSet(int n) 
        {
            parent.resize(n + 1);
            rank.resize(n + 1, 0);
            for (int i = 1; i <= n; i++) 
                parent[i] = i;
        }
    
        int find(int x) 
        {
            if (parent[x] != x) 
                parent[x] = find(parent[x]);
            return parent[x];
        }
    
        bool unionSets(int x, int y) 
        {
            int px = find(x);
            int py = find(y);
            
            if (px == py) return false;
            
            if (rank[px] < rank[py]) 
                swap(px, py);
            
            parent[py] = px;
            
            if (rank[px] == rank[py]) 
                rank[px]++;
            
            return true;
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
