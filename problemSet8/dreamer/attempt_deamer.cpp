
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

int numDigits(int& n) 
{
    return to_string(n).length();
}

bool isLeapYear(int year) 
{
    if (year % 400 == 0) 
        return true;
    if (year % 100 == 0) 
        return false;
    if (year % 4 == 0) 
        return true;
    return false;
}

bool isValidDate(int day, int month, int year) {
    // Check year range (must be 2000 or later)
    if (year < 2000) 
        return false;
    
    // Check month range
    if (month < 1 || month > 12) 
        return false;
    
    // Check day range
    int daysInMonth;
    switch (month) 
    {
        case 2: // February
            daysInMonth = isLeapYear(year) ? 29 : 28;
            break;
        case 4: 
        case 6: 
        case 9: 
        case 11: // April, June, September, November
            daysInMonth = 30;
            break;
        default: // January, March, May, July, August, October, December
            daysInMonth = 31;
            break;
    }
    
    return (day >= 1 && day <= daysInMonth);
}

bool compareDates(const tuple<int, int, int>& date1, const tuple<int, int, int>& date2) 
{
    auto& [day1, month1, year1] = date1;
    auto& [day2, month2, year2] = date2;

    // debug
    // cout << "Check:\n";
    // printf("%d-%d-%d\n",day1, month1, year1);
    // printf("%d-%d-%d\n",day2, month2, year2);


    // int year1 = get<2>(date1);
    // int year2 = get<2>(date2);
    
    if (year1 != year2) return year1 < year2;
    
    // int month1 = get<1>(date1);
    // int month2 = get<1>(date2);
    
    if (month1 != month2) return month1 < month2;
    
    // return get<0>(date1) < get<0>(date2);
    return day1 < day2;
}

void solve(vector<int>& date)
{
    vector<int> digits;
    for (int& i : date)
    {
        digits.push_back(i);
        if (numDigits(i) < 2)
            digits.push_back(0);
    }

    // for (int& i : date)
    //     cout << i << " ";

    sort(digits.begin(), digits.end());

    int numValidDates = 0;
    tuple<int, int, int> earliestDate = {-1, -1, -1};
    bool foundValidDate = false;

    do 
    {
        int day = digits[0] * 10 + digits[1];
        int month = digits[2] * 10 + digits[3];
        int year = digits[4] * 1000 + digits[5] * 100 + digits[6] * 10 + digits[7];

        // printf("Current perm: %d-%d-%d\n",day, month, year);

        // Check if this forms a valid date after Jan 1, 2000
        if (isValidDate(day, month, year)) {
            numValidDates++;
            
            // Check if this is earlier than our current earliest date
            tuple<int, int, int> currentDate = {day, month, year};
            if (!foundValidDate || compareDates(currentDate, earliestDate)) {
                earliestDate = currentDate;
                foundValidDate = true;
            }
        }
        
    } while(next_permutation(digits.begin(), digits.end()));

    if (numValidDates == 0) 
        cout << "0" << endl;
    else 
    {
        // Format day and month with leading zeros if needed
        printf("%d %02d %02d %04d\n", numValidDates, get<0>(earliestDate), get<1>(earliestDate), get<2>(earliestDate));
    }
}

int main()
{
    int t;
    cin >> t;

    while (t > 0)
    {
        // cout << "hey " << t << endl;
        int day, month, year;
        cin >> day;
        cin >> month;
        cin >> year;
        vector<int> date;
        date.push_back(day);
        date.push_back(month);
        date.push_back(year);
        solve(date);
        t--;
    }

    return 0;
}

