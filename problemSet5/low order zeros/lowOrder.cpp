
/*
https://open.kattis.com/problems/loworderzeros?tab=metadata

*/

#include<stdio.h>
#include<sstream>
#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int main()
{
    unordered_map<size_t, size_t> cache;    // key: an number to compute low order digit, Value: the low order digit

    vector<string> outVec;
    string input;
    while(getline(cin, input) && input != "")
    {
        istringstream iss(input);
        size_t num;
        iss >> num;

        if (num == 0)
            break;
        else if (cache.count(num))  // check if `num` has been calculate before
        {
            outVec.push_back(to_string(cache[num]));
            continue;
        }

        // compute the low order digit for `num`
        size_t resultSoFar = num;
        for (size_t i = num - 1; i > 0; i--)
        {
            resultSoFar *= i;
            size_t modResult = resultSoFar % 10;
            if (modResult != 0)     // case 1: take the last digit (right most digit) 
                resultSoFar = modResult;    // THIS IS NOT WORKING (RUN 25! EXAMPLE)
            else                    // case 2: remove the trailing 0s
                while (resultSoFar % 10 == 0)
                    resultSoFar = (resultSoFar / 10);
                resultSoFar = resultSoFar % 10; // do a mod here to remove any significant digits
        }
        cache[num] = resultSoFar;   // add into the cache
        outVec.push_back(to_string(resultSoFar));   // add to output
    }

    // print output
    for (string s : outVec)
        cout << s << endl;
    
    return 0;
}


/*
Test cases:
3! -> 6
25! = 15511210043330985984000000 -> 4
492! = 3304..94810368000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 -> 8

thinking:
20! = 2432902008176640000 -> 4
20 = 2^2 * 5
400!= 6403...91008000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 -> 8
40!= will not result in 4
*/
