#include <iostream>
#include <vector>
#include <cstdio>

// Fast I/O using getchar and putchar
inline int readInt() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch - '0');
        ch = getchar();
    }
    return x;
}

inline char readChar() {
    char ch = getchar();
    while (ch != '=' && ch != '?') ch = getchar();
    return ch;
}

inline void writeString(const char* s) {
    while (*s) putchar(*s++);
}

// Optimized disjoint set implementation
class DisjointSet {
private:
    int* parent;
    int* rank;

public:
    DisjointSet(int n) {
        parent = new int[n];
        rank = new int[n]();  // Initialize to zero
        
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    ~DisjointSet() {
        delete[] parent;
        delete[] rank;
    }

    // Find with path compression using iterative approach to avoid stack overflow
    int find(int x) {
        int root = x;
        
        // Find the root
        while (parent[root] != root) {
            root = parent[root];
        }
        
        // Compress path
        while (parent[x] != root) {
            int next = parent[x];
            parent[x] = root;
            x = next;
        }
        
        return root;
    }

    // Union by rank
    void unionSets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return;
        }

        if (rank[root_x] < rank[root_y]) {
            parent[root_x] = root_y;
        } else {
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) {
                rank[root_x]++;
            }
        }
    }

    // Check if two elements are in the same set
    bool sameSet(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    // Even faster than iostream with sync disabled
    int n = readInt();
    int q = readInt();

    DisjointSet ds(n);

    char op;
    int a, b;
    
    for (int i = 0; i < q; i++) {
        op = readChar();
        a = readInt();
        b = readInt();
        
        if (op == '=') {
            ds.unionSets(a, b);
        } else { // op == '?'
            if (ds.sameSet(a, b)) {
                writeString("yes\n");
            } else {
                writeString("no\n");
            }
        }
    }

    return 0;
}
