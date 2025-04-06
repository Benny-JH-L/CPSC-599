
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/ubd4aa/problems/grid

*/

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int main() 
{
    int n, m;
    string input;
    getline(cin, input);
    istringstream iss(input);
    iss >> n >> m;
    
    vector<string> grid(n);
    // read the grid
    for (int i = 0; i < n; i++) 
        cin >> grid[i];
    
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<tuple<int, int, int>> q; // (row, col, moves)
    
    q.push({0, 0, 0});
    visited[0][0] = true;
    
    // direction arrays for up, right, down, left
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    
    while (!q.empty()) 
    {
        auto& [r, c, moves] = q.front();
        q.pop();
        
        // if we've reached the bottom-right corner
        if (r == n - 1 && c == m - 1) 
        {
            cout << moves << endl;
            return 0;
        }
        
        // get the number of squares to jump
        int k = grid[r][c] - '0';
        
        // try all four directions
        for (int d = 0; d < 4; d++) 
        {
            int nr = r + dr[d] * k;
            int nc = c + dc[d] * k;
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc])     // check if the new position is valid and not visited
            {
                visited[nr][nc] = true;
                q.push({nr, nc, moves + 1});
            }
        }
    }
    
    cout << -1 << endl;
    return 0;
}
