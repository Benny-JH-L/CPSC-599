
// E.

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    vector<long long int> diffs;
    string line;
    // Go through each line
    while (getline(cin, line))
    {
        istringstream isInts(line);

        if (line.empty() || isInts.eof())
            break;
        long long int a, b;
        isInts >> a >> b;
        diffs.push_back(abs(a-b));
        // cout << "Found: " << a << " " << b << endl;
    }
    
    for (int i = 0; i < diffs.size(); i++)
    {
        cout << diffs[i] << endl;    
    }

    cout << "Exit" << endl;
    return 0;
}
