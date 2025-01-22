
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/b7bqkq/problems/birthdayboy
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>    // for sorting algo.

using namespace std;

static vector<int> monthsWith30Days = {4, 6, 9, 11};
static vector<int> monthsWith31Days = {1, 3, 5, 7, 8, 10, 12};
static unordered_map<int, int> daysInMonthMap;

// calculates the number of days apart the b-day is 
// from the end of the month
int calcNumDaysFromBdayToEOM(int& month, int& day)
{
    int daysInMonth = daysInMonthMap[month];
    return day - daysInMonth;
}

// calculates the number of days apart the b-day is 
// from the start of the month
int calcNumDaysFromBdayToSOM(int& month, int& day)
{
    return day - 1;
}

int main()
{
    // testing
    // string test = "09-19";
    // int month, day;

    // istringstream isss(test);
    // char separater23;
    // isss >> month >> separater23 >> day;

    // cout << "Month: " << month << " | Day: " << day << endl;

    // end of test

    // Create hash map that contains the # of days in each month
    for (int i : monthsWith30Days)
        daysInMonthMap[i] = 30;
    for (int i : monthsWith31Days)
        daysInMonthMap[i] = 31;
    daysInMonthMap[2] = 28;

    // Get employee birthdays and store into a hash map
    int numEmployee = 101, counter = 0;
    bool gotNumEmployee = false;
    string line;
    unordered_map<int, vector<int>> employeeBDaysMap; // first element is the month, second element is a vector of days

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
        employeeBDaysMap[month].push_back(day);

        counter++;
    }

    // sort the days in vector<int> in hashmap in ascending order
    for (int month = 1; month <= 12; month++)
    {
        if (employeeBDaysMap[month].size() > 1)
            sort(employeeBDaysMap[month].begin(), employeeBDaysMap[month].end());
    }
    
    // debug : print out hash map
    cout << endl;
    for (int month = 1; month <= 12; month++)
    {
        cout << "Month = " << month << endl;
        cout << "Days: ";
        for (int v : employeeBDaysMap[month])
        {
            cout << v << ", ";
        }
        cout << endl;
    }

    // calculate longest b-day gap that's closest to Oct 27 but that's also after it.
    tuple<int, int>* initialBDayTuple = nullptr; // first elem is month, second elem is day

    for (int month = 1; month <= 12; month++)
    {
        if (employeeBDaysMap[month].size() > 0)
        {
            initialBDayTuple = new tuple(month, employeeBDaysMap[month][0]);
            break;
        }
    }

    // debug
    auto [m, d] = *initialBDayTuple;
    cout << "initial b-day: month = " << m << " | day = " << d; 

    tuple<int, int>* compareBDayTuple = initialBDayTuple; // first elem is month, second elem is day
    int lengthOfGapInDays = 0;

    for (int month = 1; month <= 12; month++)
    {
        vector<int>* employeeBDaysAtMonth = &employeeBDaysMap[month];
        for (int i = 0; i < employeeBDaysAtMonth->size(); i++)
        {
            auto [monthComp, dayComp] = *compareBDayTuple;
            int employeeBdayDay = employeeBDaysAtMonth->at(i);
            // case, b-days are in the same month
            if (month == monthComp)
            {
                int newLength = employeeBdayDay - dayComp;  // compare the employee's b-day day with longest gap b-day day
                newLength > lengthOfGapInDays ? lengthOfGapInDays = newLength : false;
            }
            // case, b-days are not in the same month
            else 
            {
                int daysFromEndOfMonth = calcNumDaysFromBdayToEOM(monthComp, dayComp);
                int daysFromStartOfMonth = calcNumDaysFromBdayToSOM(month, employeeBdayDay);

                // calculate rest of days, ex. if jan to march, add the days in feb to daysFromEndOfMonth and daysFromStartOfMonth
            }
        }
    }

    // case, check b-days in dec to ones in jan



    return 0;
}
