
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/b7bqkq/problems/birthdayboy
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
// #include <unordered_map>
#include <algorithm>    // for sorting algo.

using namespace std;

// static unordered_map<int, int> daysInMonthMap;

int main()
{

    // vector<int> monthsWith30Days = {4, 6, 9, 11};
    // vector<int> monthsWith31Days = {1, 3, 5, 7, 8, 10, 12};

    // for (int i : monthsWith30Days)
    //     daysInMonthMap[i] = 30;
    // for (int i : monthsWith31Days)
    //     daysInMonthMap[i] = 31;
    // daysInMonthMap[2] = 28;

    vector<int> vectorMonthSum = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int currentDay = 273 + 27;

    // Get employee birthdays and store into a hash map
    int numEmployee = 101, counter = 0;
    bool gotNumEmployee = false;
    string line;
    vector<int> employeeBDaysInDays;

    while(counter < numEmployee && getline(cin, line) && line != "")
    {
        if (!gotNumEmployee)
        {
            numEmployee = stoi(line);
            gotNumEmployee = true;
            continue;
        }

        istringstream iss(line);
        int month, day;
        string employeeName;
        char separator;
        iss >> employeeName >> month >> separator >> day;

        employeeBDaysInDays.push_back(vectorMonthSum[month - 1] + day);
        counter++;
    }

    sort(employeeBDaysInDays.begin(), employeeBDaysInDays.end());

    int dayOfLongestGap = 0, gap = 0;
    for (int i = 0; i < employeeBDaysInDays.size() - 1; i++)
    {
        int tmpGap = employeeBDaysInDays[i + 1] - employeeBDaysInDays[i];
        if (tmpGap > gap)
        {
            gap = tmpGap;
            dayOfLongestGap = employeeBDaysInDays[i + 1];
        }
        else if (tmpGap == gap) // get day that is cloests to Oct 27.
        {
            int tmp1 = currentDay - dayOfLongestGap;
            int tmp2 = currentDay - employeeBDaysInDays[i + 1];

            if (tmp1 <= tmp2)
                dayOfLongestGap = tmp1;
        }
    }



    return 0;
}

