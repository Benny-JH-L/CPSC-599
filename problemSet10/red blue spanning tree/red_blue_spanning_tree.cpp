
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/jkrmjr/problems/redbluetree
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int find(vector<int>& d, int a) 
{
    if (d[a] == -1) 
        return a;
    
    return d[a] = find(d, d[a]);
}

void join(vector<int>& d, int a, int b) 
{
    a = find(d, a);
    b = find(d, b);

    if (a == b) 
        return;
    
    d[a] = b;
}

int main() 
{
    string input;
    int n, m, k;
    getline(cin, input);
    istringstream iss(input);
    iss >> n >> m >> k;

    vector<int> d1(n, -1);
    vector<int> d2(n, -1);

    for(int i = 0; i < m && getline(cin, input); i++) 
    {
        char c;
        int n1, n2;
        iss = istringstream(input);
        iss >> c >> n1 >> n2;
        n1--; n2--;

        if(c == 'R') 
            join(d1, n1, n2);
        else 
            join(d2,n1,n2);
    }

    int blue_avail = 0;
    for(int i = 0; i < n; i++) 
    {
        if(d2[i] != -1) 
            blue_avail++;
    }

    int blue_need = 0;
    for(int i = 0; i < n; i++) 
    {
        if(d1[i] == -1) 
            blue_need++;
    }
    blue_need--;

    if(blue_avail < k || blue_avail < blue_need || blue_need > k) 
        cout << 0 << endl;
    else 
        cout << 1 << endl;
}
