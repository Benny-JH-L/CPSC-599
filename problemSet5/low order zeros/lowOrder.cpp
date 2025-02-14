
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
        // this might work
        size_t resultSoFar = 2;
        for (size_t i = 3; i <= num; i++)
        {
            resultSoFar *= i;
            while (resultSoFar % 10 == 0)  
            {
                resultSoFar = (resultSoFar / 10);   // remove trailing zeros
                if (resultSoFar % 10 != 0)          // remove leading digits
                {
                    resultSoFar = resultSoFar % 10;
                }
            }
        }
        if (resultSoFar % 10 != 0)                  // remove leading digits
            resultSoFar = resultSoFar % 10;

        // Attempt 2: Failed 2nd case in submition
        // size_t resultSoFar = num;
        // for (size_t i = 2; i < num; i++)
        // {
        //     resultSoFar *= i;
        //     while (resultSoFar % 10 == 0)  
        //     {
        //         resultSoFar = (resultSoFar / 10);   // remove trailing zeros
        //         if (resultSoFar % 10 != 0)          // remove leading digits
        //         {
        //             resultSoFar = resultSoFar % 10;
        //         }
        //     }
        // }
        // if (resultSoFar % 10 != 0)                  // remove leading digits
        //     resultSoFar = resultSoFar % 10;

        // (tried to do a diff implmentation to see some diff results)
        // size_t resultSoFar = num;
        // for (size_t i = 2; i < num; i++)
        // {
        //     size_t tmp = i;
        //     // while (tmp % 10 == 0)   // remove trailing 0s
        //     //     tmp = tmp / 10;
        //     if (tmp % 10 != 0)  // remove leading digits --?
        //         tmp = tmp % 10;
        //     resultSoFar *= tmp;
        //     while (resultSoFar % 10 == 0)  
        //     {
        //         resultSoFar = (resultSoFar / 10);   // remove trailing zeros
        //         if (resultSoFar % 10 != 0)  
        //         {
        //             resultSoFar = resultSoFar % 10;
        //         }
        //     }
        // }

        // ATTTMPT 1 (DOES NOT WORK FOR ALL CASES I FOUND), and failed 2nd case in submition
        // ssize_t resultSoFar = num;
        // for (ssize_t i = num - 1; i > 0; i--)
        // {
        //     if (i == 4)
        //         int s = 2;
        //     resultSoFar *= i;
        //     ssize_t modResult = resultSoFar % 10;
        //     // if (modResult != 0)     // case 1: take the last digit (right most digit) 
        //     //     resultSoFar = modResult;    // THIS IS NOT WORKING (RUN 25! EXAMPLE)
        //     // else                    // case 2: remove the trailing 0s
        //     // {
        //         while (resultSoFar % 10 == 0)
        //             resultSoFar = (resultSoFar / 10);
        //         resultSoFar = resultSoFar % 10; // do a mod here to remove any significant digits
        //     // }
        // }

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
49! = 608281...0240000000000

*/
