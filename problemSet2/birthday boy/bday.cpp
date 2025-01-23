
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/b7bqkq/problems/birthdayboy
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>    // for sorting algo.

#define OCTOBER = 10;

using namespace std;

tuple<int, int> getNextBday(tuple<int, int> bday);
int calcDaysBetweenMonths(int startMonth, int endMonth);
int calcGap(tuple<int, int> startingDate, tuple<int, int> endDate);

static unordered_map<int, int> daysInMonthMap;
static unordered_map<int, vector<int>> employeeBDaysMap; // first element is the month, second element is a vector of days

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
    vector<int> monthsWith30Days = {4, 6, 9, 11};
    vector<int> monthsWith31Days = {1, 3, 5, 7, 8, 10, 12};

    for (int i : monthsWith30Days)
        daysInMonthMap[i] = 30;
    for (int i : monthsWith31Days)
        daysInMonthMap[i] = 31;
    daysInMonthMap[2] = 28;

    // Get employee birthdays and store into a hash map
    int numEmployee = 101, counter = 0;
    bool gotNumEmployee = false;
    string line;

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
    
    // debug : print out employeeBDaysMap hash map
    // cout << endl;
    // for (int month = 1; month <= 12; month++)
    // {
    //     cout << "Month = " << month << endl;
    //     cout << "Days: ";
    //     for (int v : employeeBDaysMap[month])
    //     {
    //         cout << v << ", ";
    //     }
    //     cout << endl;
    // }

    tuple<int, int> initialBDayTuple; // first elem is month, second elem is day
    // find first b-day and set value
    for (int month = 1; month <= 12; month++)
    {
        if (employeeBDaysMap[month].size() > 0)
        {
            initialBDayTuple = tuple(month, employeeBDaysMap[month][0]);
            break;
        }
    }

    // debug
    auto [m, d] = initialBDayTuple;
    cout << "initial b-day: month = " << m << " | day = " << d << endl; 

    tuple<int, int> t1(1, 9);
    tuple<int, int> t2(9, 9);
    tuple<int, int> t3 (11, 9);
    int g000 = calcGap(t1, t2);
    cout << "gap (days) from 01-09 to 09-20 is: " << g000 << endl; // expected gap of 242
    int g001 = calcGap(t2, t3);
    cout << "gap (days) from 09-09 to 11-09 is: " << g001 << endl; // expected gap of 60
    tuple<int, int> t4(10, 2);
    tuple<int, int> t5(11, 29);
    int g002 = calcGap(t5, t4);
    cout << "gap (days) from 11-29 to 10-02 is: " << g002 << endl; // expected gap of 306
    tuple<int, int> t6(2, 19);
    tuple<int, int> t7(2, 5);
    int g003 = calcGap(t6, t7);
    cout << "gap (days) from 02-19 to 2-05  is: " << g003 << endl; // expected gap of 352
    tuple<int, int> t8(4, 2);
    tuple<int, int> t9(4, 10);
    int g004 = calcGap(t8, t9);
    cout << "gap (days) from 04-02 to 4-10  is: " << g004 << endl; // expected gap of 7

    cout << "tuple<1,9> == tuple<9,9> : " << (t1 == t2) << endl;

    if (t1 == t2) 
    {
        cout << "AHHHHH";
    }

    // end of debug--

    // calculate longest b-day gap that's closest to Oct 27 but that's also after it.
    tuple<int, int> bdayToCompareTuple = initialBDayTuple; // first elem is month, second elem is day
    int bdayGap = 0, c = 1;

    while ((bdayToCompareTuple != initialBDayTuple) == 1 || c == 1)
    {
        tuple<int, int> nextBday = getNextBday(bdayToCompareTuple);

        c++;
        break;  // keep this until implemented so it does not loop infinetly...
    }


    return 0;
}

tuple<int, int> getNextBday(tuple<int, int> bday)
{
    auto [initialM, initialD] = bday;

    // counts how many elememts we've gone through in the hashmap, 
    //when this equals the hashmap size then we've gone through all elements
    int hashMapCounter = 0, bDaysMapSize = employeeBDaysMap.size(); 
   
    for (int monthKey = initialM; hashMapCounter < employeeBDaysMap.size(); monthKey = (monthKey + 1) % 12)
    {
        // find where this bday is situated
        int vectorSize = employeeBDaysMap[initialM].size();
        for (int i = 0; i < vectorSize; i++)
        {
            int dayToCheck = employeeBDaysMap[initialM][i];
            if (initialD == dayToCheck)
            {
                // see one note for cases
            }
        }  
    }


    // for ()
    // {
    //     for (int index = 0; index < employeeBDaysMap[].size(); index++)
    //     {

    //     }
    // }
}

int calcDaysBetweenMonths(int startMonth, int endMonth)
{
    int numMonthsBetween = 0, numDays = 0;

    for (int count = startMonth + 1; count != endMonth; count = (count + 1) % 12)
	    numMonthsBetween++;
    
    for (int currentMonth = startMonth + 1, counter = 0; counter < numMonthsBetween; counter++, currentMonth = (currentMonth + 1) % 12)
		numDays += daysInMonthMap[currentMonth];

    return numDays;
}

int calcGap(tuple<int, int> startingDate, tuple<int, int> endDate)
{
    int gap = 0;
    auto [startingM, startingD] = startingDate;
    auto [endM, endD] = endDate;
    
    if (startingM != endM)
    {
        int numDaysFromFirstOfMonth = endD - 1;
        int numDaysFromEndOfMonth = daysInMonthMap[startingM] - startingD;
        
        gap = numDaysFromEndOfMonth + calcDaysBetweenMonths(startingM, endM) + numDaysFromFirstOfMonth;
    }
    else
    {
        if (endD < startingD)   // b-days in the same month but the next birthday is next year
            gap = 365 - (abs(endD - startingD) - 1);
        else                    // b-days in the same month in the same year
            gap = (abs(endD - startingD) - 1);
    }
    
    return gap;
}

// OLD
    // tuple<int, int>* compareBDayTuple = initialBDayTuple; // first elem is month, second elem is day
    // int lengthOfGapInDays = 0;

    // for (int month = 1; month <= 12; month++)
    // {
    //     vector<int>* employeeBDaysAtMonth = &employeeBDaysMap[month];
    //     for (int i = 0; i < employeeBDaysAtMonth->size(); i++)
    //     {
    //         auto [montOfEnd, dayOfEnd] = *compareBDayTuple;
    //     }
    // }


//     int calcGap(tuple<int, int>* startingDate, tuple<int, int>* endDate)
// {
//     int gap = 0;
//     auto [startingM, startingD] = *startingDate;
//     auto [endM, endD] = *endDate;

//     if (startingM < endM)
//     {
//         int numDaysFromFirstOfMonth = endD - 1;
//         int numDaysFromEndOfMonth = daysInMonth[startingM] - startingD;
        
//         gap = numDaysFromEndOfMonth + calcDaysBetweenMonths(startingM, endM) + numDaysFromFirstOfMonth;
//     }
//     else if (endM < startingM)
//     {
//         int numDaysFromFirstOfMonth = endD - 1;
//         int numDaysFromEndOfMonth = daysInMonth[startingM] - startingD;

//         gap = numDaysFromEndOfMonth + calcDaysBetweenMonths(startingM, endM) + numDaysFromFirstOfMonth;
//     }
//     else
//     {
//         if (endD < startingD)
//             gap = 365 - (abs(endD - startingD) - 1);
//         else
//             gap = (abs(endD - startingD) - 1);
//     }
    
//     return gap;
// }
