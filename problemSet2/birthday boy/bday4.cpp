
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/b7bqkq/problems/birthdayboy
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>    // for sorting algo.
#include <set>
#include <tuple>

using namespace std;

void gapTest();
void nextBdayTest();

static unordered_map<int, int> daysInMonthMap;
static unordered_map<int, set<int>> bdayMap;
static tuple<int, int> oct27(10, 27);

int calcDaysBetweenMonths(int startMonth, int endMonth) // helper func for 'calcGap'
{
    int numMonthsBetween = 0, numDays = 0;
    int count = (startMonth + 1) % 13;
    count == 0 ? count = 1 : false;

    for (; count != endMonth; count = (count + 1) % 13)
	    numMonthsBetween++;
    
    int currentMonth = (startMonth + 1) % 13;
    currentMonth == 0 ? currentMonth = 1 : false;
    for (int counter = 0; counter < numMonthsBetween; counter++, currentMonth = (currentMonth + 1) % 13)
		numDays += daysInMonthMap[currentMonth];

    return numDays;
}

int calcGap(tuple<int, int> startingDate, tuple<int, int> endDate)
{
    int gap = 0;
    auto [startingM, startingD] = startingDate;
    auto [endM, endD] = endDate;

    // same bday -> return 0 gap
    if (startingM == endM && startingD == endD)
        return gap;
    
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

    // debug
    cout << startingM << "-" << startingD << " to " << endM << "-" << endD << " | Gap: " << gap << endl; 

    return gap;
}

tuple<int, int> getNextbday(tuple<int, int> currentbday)
{
    tuple<int, int> returnTup = currentbday;
    auto [currM, currD] = currentbday;

    bool nextBDayInAnotherMonth = true;
    for (int day :  bdayMap[currM])
    {
        if (day > currD)
        {
            returnTup =  make_tuple(currM, day);
            nextBDayInAnotherMonth = false;
            break;
        }
    }

    for (int monthKey = currM + 1, counter = 0; nextBDayInAnotherMonth && counter < bdayMap.size() ; monthKey = (monthKey + 1) % 13, counter++)
    {
        if (bdayMap[monthKey].size() > 0)  // return the month's first bday 
        {
            returnTup = make_tuple(monthKey, *bdayMap[monthKey].begin());   
            break;
        }
    }

    // debug
    auto [m1, d1] = returnTup;
    cout << "bday after " << currM << "-" << currD << " is " << m1 << "-" << d1 << endl;

    return returnTup; // if there no/or 1 bday's inside the map, return the input.
}

int main()
{
    // initialize map
    vector<int> monthsWith30Days = {4, 6, 9, 11};
    vector<int> monthsWith31Days = {1, 3, 5, 7, 8, 10, 12};

    for (int i : monthsWith30Days)
        daysInMonthMap[i] = 30;
    for (int i : monthsWith31Days)
        daysInMonthMap[i] = 31;
    daysInMonthMap[2] = 28;

    // testing
    // gapTest();
    nextBdayTest();
    // end of test

    // Get employee birthdays and store into a hash map
    int numEmployee = 101, counter = 0;
    string line;
    getline(cin, line);
    istringstream iss(line);
    iss >> numEmployee;

    while(counter < numEmployee && getline(cin, line) && line != "")
    {
        iss = istringstream(line);
        int month, day;
        string employeeName;
        char separator;
        iss >> employeeName >> month >> separator >> day;
        bdayMap[month].insert(day);
        counter++;
    }

    // nextBdayTest(); // debug

    tuple<int, int> firstbdayAfterOct27 = getNextbday(oct27);
    auto [firstbdayAfterOct27M, firstbdayAfterOct27D] = firstbdayAfterOct27;
    tuple<int, int> bdayToCompare = firstbdayAfterOct27;
    tuple<int, int> longestRunningbday = firstbdayAfterOct27;
    int longestGap = calcGap(oct27, firstbdayAfterOct27);

    while(true)
    {
        tuple<int, int> nextbday = getNextbday(bdayToCompare);
        auto [nextbdayM, nextbdayD] = nextbday;
        // auto [m1, d1] = bdayToCompare;
        
        int gapTmp = calcGap(bdayToCompare, nextbday);

        if (gapTmp > longestGap)
        {
            longestGap = gapTmp;
            longestRunningbday = nextbday;
        }
        else if (gapTmp == longestGap)  // case, check which bday is the soonest
        {
            int tmp1 = calcGap(oct27, longestRunningbday);
            int tmp2 = calcGap(oct27, nextbday);

            if (tmp1 == 0)
                longestRunningbday = nextbday;
            else if (tmp2 != 0 && tmp2 < tmp1)
            {
                longestRunningbday = nextbday;
            }
        }

        if (nextbdayM == firstbdayAfterOct27M && nextbdayD == firstbdayAfterOct27D) // if nextbday is the samebday as firstbdayAfterOct27, then exit loop
            break;

        bdayToCompare = nextbday;
    }

    auto [longestRunningMonth, longestRunningDay] = longestRunningbday;
    cout << "\nThe longest running bday (makes longest gap) is: " << longestRunningMonth << '-' << longestRunningDay << endl;

    // calc Bobby's fake b-day

}

void gapTest()
{
    tuple<int, int> oct27(10, 27); // NOTE: a b-day can also occur today (Oct 27)!

    tuple<int, int> dec31(12, 31);
    tuple<int, int> jan1(1, 1);
    tuple<int, int> feb1(2, 1);
    tuple<int, int> march1(3, 1);
    calcGap(jan1, dec31); // expected 365 - 2 = 363
    calcGap(dec31, jan1); // expected 0
    calcGap(dec31, feb1); // expected 31
    calcGap(dec31, march1); // expected 59
    cout << endl;

    
    tuple<int, int> jan9(1, 9);
    tuple<int, int> sept20(9, 20);
    tuple<int, int> nov11(11, 11);
    calcGap(jan9, sept20); // expected 253
    calcGap(sept20, nov11); // expected 51
    calcGap(oct27, nov11); // expected 14
    calcGap(nov11, jan9);
    cout << endl;

    cout << "---" << endl;
    tuple<int, int> april29(4, 29);
    tuple<int, int> oct28(10, 28);
    tuple<int, int> april28(4, 28);
    calcGap(april28, april29); // expected
    calcGap(april29, oct28); // expected
    calcGap(oct27, oct28); // expected (START FINDING B-DAYS FROM OCT 27)
    calcGap(oct28, april28); // expected
    cout << endl;
    calcGap(april29, oct28);
    calcGap(oct27, oct28);
    calcGap(oct27, april28);
    cout << "---" << endl;

    cout << "---" << endl;
    tuple<int, int> april30(4, 30);
    tuple<int, int> oct29(10, 29);
    // tuple<int, int> april29(4, 29); // already defined
    calcGap(april29, april30); // expected
    // calcGap(april30, oct27); // expected 179
    calcGap(april30, oct29); // expected 181
    calcGap(oct27, oct29); // expected
    calcGap(oct29, april29); // expected 181
    cout << endl;
    calcGap(april30, oct29); // expected 181
    // calcGap(oct27, oct29); // expected 1
    calcGap(oct27, april29); // expected 183
    cout << "---" << endl;


    calcGap(oct27, oct28);
    calcGap(oct28, oct28);
}

void addTupleToBdayMap( tuple<int, int> tup)    // helper function
{
    auto [key, day] = tup;
    bdayMap[key].insert(day);
}

void nextBdayTest()
{
    bdayMap.clear();

    // when there are 'no' bdays
    tuple<int, int> oct27(10, 27); // NOTE: a b-day can also occur today (Oct 27)!
    getNextbday(oct27);

    // when there is 1 bday
    cout << endl;
    addTupleToBdayMap(oct27);
    getNextbday(oct27);
    bdayMap.clear();

    cout << endl;
    tuple<int, int> jan9(1, 9);
    tuple<int, int> sept20(9, 20);
    tuple<int, int> nov11(11, 11);
    addTupleToBdayMap(jan9);
    addTupleToBdayMap(sept20);
    addTupleToBdayMap(nov11);
    getNextbday(jan9);          // expected is 9-20
    getNextbday(sept20);         // expected is 11-1
    getNextbday(nov11);         // expected is 1-9
    bdayMap.clear();
}
