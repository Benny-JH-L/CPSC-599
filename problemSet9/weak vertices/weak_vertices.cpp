
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/bcty6b/problems/weakvertices
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isWeakVertex(int vertex, const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    
    // Check if this vertex forms a triangle with any pair of its neighbors
    for (int j = 0; j < n; j++) 
    {
        // If j is a neighbor of vertex
        if (adjMatrix[vertex][j] == 1) 
        {
            for (int k = j + 1; k < n; k++) 
            {
                // If k is also a neighbor of vertex
                if (adjMatrix[vertex][k] == 1) 
                {
                    // Check if j and k are connected (forming a triangle)
                    if (adjMatrix[j][k] == 1)     
                        return false; // Found a triangle
                }
            }
        }
    }
    
    // No triangle found for this vertex
    return true;
}

int main() 
{
    int n;
    
    while (true) 
    {
        cin >> n;
        if (n == -1) 
            break;
        
        // Read the adjacency matrix
        vector<vector<int>> adjMatrix(n, vector<int>(n));
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
                cin >> adjMatrix[i][j];
        }
        
        // Find weak vertices
        vector<int> weakVertices;
        for (int i = 0; i < n; i++) 
        {
            if (isWeakVertex(i, adjMatrix)) 
                weakVertices.push_back(i);
        }
        
        // Print the weak vertices
        for (size_t i = 0; i < weakVertices.size(); i++) 
        {
            cout << weakVertices[i];
            if (i < weakVertices.size() - 1) 
                cout << " ";
        }
        cout << endl;
    }
    
    return 0;
}
