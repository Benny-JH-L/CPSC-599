/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/ubd4aa/problems/allpairspath
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

const int INF = 10e8;

struct Edge 
{
    int from, to, weight;
};

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    while (true) 
    {
        cin >> n >> m >> q;
        if (n == 0 && m == 0 && q == 0) break;
        
        cin.clear();
        
        Edge edges[m];
        // vector<Edge> edges(m);
        vector<vector<int>> graph(n);

        for (int i = 0; i < m; i++) 
        {
            Edge& e = edges[i];
            cin >> e.from >> e.to >> e.weight;
            graph[e.from].push_back(e.to);

            // cin >> edges[i].from >> edges[i].to >> edges[i].weight;
            // graph[edges[i].from].push_back(edges[i].to);
        }

        for (int i = 0; i < q; i++) 
        {
            int source, target;
            cin >> source >> target;
            
            vector<int> dist(n, INF);
            dist[source] = 0;
            
            for (int j = 0; j < n - 1; j++) 
            {
                for (const Edge& e : edges) 
                {
                    if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.weight)
                        dist[e.to] = dist[e.from] + e.weight;
                }
            }
            
            vector<bool> hasNegCycle(n, false);
            
            for (int j = 0; j < n; j++) 
            {
                for (const Edge& e : edges) 
                {
                    if (dist[e.from] != INF && dist[e.to] > dist[e.from] + e.weight)
                        hasNegCycle[e.to] = true;
                }
            }
            
            for (int j = 0; j < n; j++) 
            {
                for (const Edge& e : edges) 
                {
                    if (dist[e.from] != INF && (dist[e.to] > dist[e.from] + e.weight || hasNegCycle[e.from])) 
                    {
                        dist[e.to] = dist[e.from] + e.weight;
                        hasNegCycle[e.to] = true;
                    }
                }
            }
            
            // Output the result
            if (dist[target] == INF)
                cout << "Impossible\n";
            else if (hasNegCycle[target])
                cout << "-Infinity\n";
            else 
                cout << dist[target] << endl;
        }
        
        cout << endl;
    }
    
    return 0;
}

