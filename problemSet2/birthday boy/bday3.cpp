
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

static unordered_map<int, int> daysInMonthMap;
static unordered_map<int, set<int>> bdayMap;

int calcDaysBetweenMonths(int startMonth, int endMonth) // helper func for 'calcGap'
{
    int numMonthsBetween = 0, numDays = 0;

    for (int count = startMonth + 1; count != endMonth; count = (count + 1) % 13)
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
    
    return gap;
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

    tuple<int, int> dec31(12, 31);
    tuple<int, int> jan9(1, 9);
    int tgap000 = calcGap(jan9, dec31);
    cout << "gap = " << tgap000 << endl;
 
    // end of test

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
        bdayMap[month].insert(day);
        counter++;
    }

    // since we don't want a b-day on Oct 27, insert it into the bdaymap
    bdayMap[10].insert(27);

    // debug : print out bdayMap hash map
    cout << endl;
    for (int month = 1; month <= 12; month++)
    {
        cout << "Month = " << month << endl;
        cout << "Days: ";
        for (int v : bdayMap[month])
        {
            cout << v << ", ";
        }
        cout << endl;
    }
    // end debug

    vector<tuple<int, int>> bdayTupVector;
    // put bdaysMap into a vector (in ascending order)
    for (int mKey = 1; mKey <= 12 ; mKey++)
    {
        for (int day : bdayMap[mKey])
        {
            bdayTupVector.push_back(make_tuple(mKey, day));
        }
    }

    // debug - print out vector
    cout << "\nbdayTupVector: ";
    for (auto [m, d] : bdayTupVector)
    {
        cout << "<" << m << ", " << d << ">, ";
    }
    cout << "\n" << endl;
    // end debug

    // calc the gap between elements at index i and i+1, when reaching the end of the vector, compare the end bday with the first bday
    int gap = 0, indexOfLongestRunningBday = 0;
    vector<tuple<tuple<int, int>, tuple<int, int>>> longestRunnningPairTuple;
    for (int i = 0; i < bdayTupVector.size(); i++)
    {
        int tmpGap = 0;
        tuple<int, int> tmpTup; // used later for gap tie's

        if (i + 1 >= bdayTupVector.size()) // case: check last bday with first bday
        {
            tuple<int, int> endBday = bdayTupVector[i];
            tuple<int, int> firstBday = bdayTupVector[0];
            tmpGap = calcGap(endBday, firstBday);

            // debug
            auto [month, day] = firstBday;
            auto [month2, day2] = endBday;
            cout << "Bday to comapre is Month: " << month2 << " | Day: " << day2 << endl;
            cout << "Bday after is Month: " << month << " | Day: " << day << endl;
            cout << "tmpGap: " << tmpGap << endl;
            // end debug

            if (tmpGap >= gap)
            {
                indexOfLongestRunningBday = 0;
                gap = tmpGap;
                longestRunnningPairTuple.push_back(make_tuple(endBday, firstBday));
                cout << "new Gap: " << gap << endl;
            }
            tmpTup = firstBday;
        }
        else
        {
            tuple<int, int> tup1 = bdayTupVector[i];
            tuple<int, int> tup2 = bdayTupVector[i+1];    // bday after index 'i'
            tmpGap = calcGap(tup1, tup2);

            // debug
            auto [month, day] = tup2;
            auto [month2, day2] = tup1;
            cout << "Bday to comapre is Month: " << month2 << " | Day: " << day2 << endl;
            cout << "Bday after is Month: " << month << " | Day: " << day << endl;
            cout << "tmpGap: " << tmpGap << endl;
            // end debug

            if (tmpGap >= gap)
            {
                indexOfLongestRunningBday = i+1;
                gap = tmpGap;
                longestRunnningPairTuple.push_back(make_tuple(tup1, tup2));
                cout << "new Gap: " << gap << endl;
            }
            tmpTup = tup2;
        }

        // find the bday closest to Oct 27 (but is after)
        // if (tmpGap == gap)
        // {
        //     tuple<int, int> october27(10, 27);
        //     int tmp1 = calcGap(october27, bdayTupVector[indexOfLongestRunningBday]);
        //     int tmp2 = calcGap(october27, tmpTup);

        //     if (tmp2 <= tmp1)
        //         indexOfLongestRunningBday = i;
        // }
    }

    // find the bday closest to Oct 27 (but is after)
    // if the result is 0, then longest b-day runs to Oct 27 (don't choose it)

    gap = 0;
    for ( auto[startBday, endBday] : longestRunnningPairTuple)
    {
        auto [startM, startD] = startBday;
        auto [endM, endD] = endBday;
        int tmpGap = calcGap(startBday, endBday);

        cout << startM << "-" << startD << " to " << endM << '-' << endD << " has gap: " << tmpGap << endl;
    }


    // debug
    auto [tmpM, tmpD] = bdayTupVector[indexOfLongestRunningBday];
    cout << "Date of longest running bday: " << tmpM << "-" << tmpD << endl;


    // find Bobby's b-day

 
    return 0;
}

    // for (int i = 0; i < longestRunnningPairTuple.size(); i++)
    // {
        
    //     auto [startM, startD] = startBday;
    //     auto [endM, endD] = endBday;

    //     cout << startM << "-" << startD << " to " << endM << '-' << endD << " has gap: " << endl;
    // }
    