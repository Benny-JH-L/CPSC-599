/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/bcty6b/problems/goodmorning
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

// Check if a number can be entered with downward/rightward movements only
bool isValid(int num) 
{
    string digits = to_string(num);
    
    for (size_t i = 0; i < digits.size() - 1; i++) 
    {
        int curr = digits[i] - '0';
        int next = digits[i+1] - '0';
        
        // Convert digit to keyboard position (row, col)
        int curr_row = (curr == 0) ? 3 : (curr - 1) / 3;
        int curr_col = (curr == 0) ? 1 : (curr - 1) % 3;
        
        int next_row = (next == 0) ? 3 : (next - 1) / 3;
        int next_col = (next == 0) ? 1 : (next - 1) % 3;
        
        // Check if next position is below or to the right of current position
        if (next_row < curr_row || next_col < curr_col) 
            return false;
    }
    
    return true;
}

// Find the closest valid number to k
int findClosestValid(int k) 
{
    int closest = -1;
    int minDiff = 201; // Max k is 200, so difference can't be more than 200
    
    // Check numbers within a reasonable range around k
    for (int num = max(1, k - 100); num <= min(999, k + 100); num++) 
    {
        if (isValid(num)) 
        {
            int diff = abs(num - k);
            if (diff < minDiff) 
            {
                minDiff = diff;
                closest = num;
            }
        }
    }
    
    return closest;
}

int main() 
{
    int t;
    cin >> t;
    
    while (t-- > 0) 
    {
        int k;
        cin >> k;
        cout << findClosestValid(k) << endl;
    }
    
    return 0;
}
