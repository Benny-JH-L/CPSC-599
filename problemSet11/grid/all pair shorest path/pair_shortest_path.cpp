/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/ubd4aa/problems/allpairspath
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = 1e9;

int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, q;
    
    while (true) 
    {
        cin >> n >> m >> q;
        if (n == 0 && m == 0 && q == 0) 
            break;

        vector<vector<int>> dist(n, vector<int>(n, INF));
        
        // distance from node to itself is 0
        for (int i = 0; i < n; i++)
            dist[i][i] = 0;
        
        // edges
        for (int i = 0; i < m; i++) 
        {
            int u, v, w;
            cin >> u >> v >> w;
            dist[u][v] = min(dist[u][v], w);
        }
        
        // Floyd-Warshall algorithm
        for (int k = 0; k < n; k++) 
        {
            for (int i = 0; i < n; i++) 
            {
                for (int j = 0; j < n; j++) 
                {
                    if (dist[i][k] != INF && dist[k][j] != INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        
        // negative cycles and their influence
        for (int k = 0; k < n; k++) 
        {
            // if node k is on a negative cycle
            if (dist[k][k] < 0) 
            {
                //find all pairs (i,j) where i can reach k and j can be reached from k
                for (int i = 0; i < n; i++) 
                {
                    if (dist[i][k] != INF) 
                    {
                        for (int j = 0; j < n; j++) 
                        {
                            if (dist[k][j] != INF) 
                                dist[i][j] = -INF; // mark dist[i][j] can be made arbitrarily small
                        }
                    }
                }
            }
        }
        
        // process queries
        for (int i = 0; i < q; i++) 
        {
            int u, v;
            cin >> u >> v;
            
            if (dist[u][v] == -INF)
                cout << "-Infinity\n";
            else if (dist[u][v] == INF)
                cout << "Impossible\n";
            else 
                cout << dist[u][v] << endl;
        }
        
        cout << endl;
    }
    
    return 0;
}
