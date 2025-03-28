
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/jkrmjr/submissions/17000207
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

// Directions for 8-way adjacency (horizontal, vertical, diagonal)
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};


bool checkLoop(vector<vector<char>>& grid, vector<vector<bool>>& visited, int startX, int startY) 
{
    int m = grid.size();
    int n = grid[0].size();
    queue<pair<int, int>> q;
    vector<pair<int, int>> loopPixels;
    
    q.push({startX, startY});
    visited[startX][startY] = true;
    loopPixels.push_back({startX, startY});

    while (!q.empty()) 
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        // check all 8 adjacent pixels
        int blackNeighbors = 0;
        vector<pair<int, int>> nextPixels;

        for (int k = 0; k < 8; k++) 
        {
            int nx = x + dx[k];
            int ny = y + dy[k];

            // check if new pixel is within grid and is a black pixel
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '#') {
                blackNeighbors++;

                // if not visited, it's a potential next pixel in the loop
                if (!visited[nx][ny]) 
                    nextPixels.push_back({nx, ny});
            }
        }

        // A valid loop pixel should have exactly 2 black neighbors
        if (blackNeighbors != 2) 
            return false;

        // Process next pixels
        for (auto& pixel : nextPixels) 
        {
            q.push(pixel);
            visited[pixel.first][pixel.second] = true;
            loopPixels.push_back(pixel);
        }
    }

    return true;
}

int countLoops(vector<vector<char>>& grid) 
{
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    int loopCount = 0;

    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            // if it's a black pixel and not visited, start a loop check
            if (grid[i][j] == '#' && !visited[i][j]) 
            {
                // check if this is the start of a loop
                bool isLoop = checkLoop(grid, visited, i, j);
                if (isLoop) 
                    loopCount++;
            }
        }
    }

    return loopCount;
}

int main() 
{
    string input;
    getline(cin, input);
    istringstream iss(input);
    int m, n;
    iss >> m >> n;
    
    // Read the grid
    vector<vector<char>> grid(m, vector<char>(n));
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
            cin >> grid[i][j];
    }

    cout << countLoops(grid) << endl;

    return 0;
}
