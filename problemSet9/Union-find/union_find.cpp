/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/bcty6b/problems/unionfind
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// O(alpha(n)), where alpha(n) is the inverse Ackermann function (almost constant).
class DisjointSet 
{
private:
    // vector<int> parent;
    // vector<int> rank;
    int* parent;
    int* rank;

public:
    DisjointSet(int n) 
    {
        // parent.resize(n);
        // rank.resize(n, 0);
        parent = new int[n];
        rank = new int[n]();  // Initialize to zero

        // Initialize each element as its own parent
        for (int i = 0; i < n; i++) 
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
    void unionSets(int x, int y) 
    {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) 
            return;

        // if (rank[root_x] < rank[root_y]) 
        //     parent[root_x] = root_y;
        // else if (rank[root_x] > rank[root_y]) 
        //     parent[root_y] = root_x;
        // else 
        // {
        //     parent[root_y] = root_x;
        //     rank[root_x]++;
        // }

        if (rank[root_x] < rank[root_y]) 
            parent[root_x] = root_y;
        else 
        {
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) 
                rank[root_x]++;
        }
    }

    // Check if two elements are in the same set
    bool sameSet(int x, int y) 
    {
        return find(x) == find(y);
    }
};

int main() 
{
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    DisjointSet ds(n);

    char op;
    int a, b;
    
    for (int i = 0; i < q; i++) 
    {
        cin >> op >> a >> b;
        
        if (op == '=') 
            ds.unionSets(a, b);
        else if (op == '?') 
        {
            if (ds.sameSet(a, b)) 
                cout << "yes\n";
            else 
                cout << "no\n";
        }
    }

    return 0;
}

