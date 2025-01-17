/*
Question link: https://open.kattis.com/problems/carpool
 */

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

int main()
{
    // I will need to use some sort of find the shortest path algorith, dijkstra's, FLoyd's etc.
    string line, tmp;
    cin >> line; // get first line containing 'n' and 'm'
    int n, m;
    istringstream iss(line);
    bool gotN = false;
    while (iss >> tmp)
    {
        // use ternery operator?
        if (!gotN)
        {
            n = stoi(tmp);
            gotN = true;
        }
        else
            m = stoi(tmp);
    }

    while (getline(cin, line) && line != "")
    {
        roadInputToRoadData(line);
    }

    return 0;
}

vector<tuple<int, int, int>> roadInputToRoadData(string roadINput)
{
    istringstream iss(roadINput);

}

