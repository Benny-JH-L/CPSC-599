
/*
https://open.kattis.com/problems/anothercandies?tab=metadata 

2^63 = 9223372036854775808

Passed all Tests!
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{

    string input;
    getline(cin, input);
    istringstream iss(input);
    int numCases = 0, numChildren = 0;
    iss >> numCases;

    vector<string> output;
    int count1 = 0;
    while (count1 < numCases && getline(cin, input))
    {
        if (input == "")
            continue;            

        iss = istringstream(input);
        iss >> numChildren;
        unsigned long long int sum = 0, numCandy = 0;
        int count2 = 0;

        while (count2 < numChildren && getline(cin, input))
        {
            iss = istringstream(input);
            iss >> numCandy;
            if (count2 + 1 >= numChildren)
            {
                if ((sum + numCandy) % numChildren == 0)
                {
                    output.push_back("YES");
                    break;
                }
                output.push_back("NO");
                break;
            }
            sum += (numCandy % numChildren);

            count2++;
        }
        count1++;
    }
    
    for (string s : output)
        cout << s << endl;
    
    return 0;
}

