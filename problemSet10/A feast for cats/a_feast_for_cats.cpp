#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Edge structure to represent distance between two cats
struct Edge {
    int u, v, weight;
    
    Edge(int _u, int _v, int _w) : u(_u), v(_v), weight(_w) {}
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// DisjointSet (Union-Find) data structure for Kruskal's algorithm
class DisjointSet {
private:
    vector<int> parent, rank;
    
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
        }
    }
};

bool canServeMilk(int milk, int cats, const vector<Edge>& edges) {
    // If there's only one cat (cat 0), we just need 1ml of milk
    if (cats == 1) {
        return milk >= 1;
    }
    
    // Create a graph with all cats as vertices
    vector<Edge> allEdges = edges;
    
    // Sort edges by their weights (distances)
    sort(allEdges.begin(), allEdges.end());
    
    // Apply Kruskal's algorithm to find the Minimum Spanning Tree
    DisjointSet ds(cats);
    int mstWeight = 0;
    
    for (const Edge& edge : allEdges) {
        if (ds.find(edge.u) != ds.find(edge.v)) {
            mstWeight += edge.weight;
            ds.unite(edge.u, edge.v);
        }
    }
    
    // We need to traverse each edge in the MST twice (going and coming back)
    // This causes us to spill 2 * MST weight amount of milk
    int milkSpilled = 2 * mstWeight;
    
    // We need at least 1ml of milk for each cat
    int milkForCats = cats;
    
    // Total milk required = milk spilled + milk needed for cats
    return milk >= (milkSpilled + milkForCats);
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int m, c;
        cin >> m >> c;
        
        vector<Edge> edges;
        
        // Read distances between pairs of cats
        for (int i = 0; i < c * (c - 1) / 2; i++) {
            int u, v, dist;
            cin >> u >> v >> dist;
            edges.push_back(Edge(u, v, dist));
        }
        
        if (canServeMilk(m, c, edges)) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
    
    return 0;
}