#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Function to check if a year is a leap year
bool isLeapYear(int year) {
    if (year % 400 == 0) 
        return true;
    if (year % 100 == 0) 
        return false;
    if (year % 4 == 0) 
        return true;
    return false;
}

// Function to check if a date is valid
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

// Function to compare dates (for finding the earliest date)
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

void solvePokenomDate(const string& digits) {
    // Parse the input digits (removing spaces)
    vector<int> digitsVector;
    for (char c : digits) 
    {
        if (isdigit(c)) 
            digitsVector.push_back(c - '0');
    }
        
    // Sort digits to prepare for permutation generation
    sort(digitsVector.begin(), digitsVector.end());
    
    // Count valid dates and track the earliest
    int validDateCount = 0;
    tuple<int, int, int> earliestDate = {31, 12, 9999}; // Initialize with a very late date
    bool foundValidDate = false;
    
    // Generate all permutations and check if they form valid dates
    do {
        // Extract day, month, and year from the current permutation
        int day = digitsVector[0] * 10 + digitsVector[1];
        int month = digitsVector[2] * 10 + digitsVector[3];
        int year = digitsVector[4] * 1000 + digitsVector[5] * 100 + digitsVector[6] * 10 + digitsVector[7];
        
        // Check if this forms a valid date after Jan 1, 2000
        if (isValidDate(day, month, year)) 
        {
            validDateCount++;
            
            // Check if this is earlier than our current earliest date
            tuple<int, int, int> currentDate = {day, month, year};
            if (!foundValidDate || compareDates(currentDate, earliestDate)) 
            {
                earliestDate = currentDate;
                foundValidDate = true;
            }
        }
    } while (next_permutation(digitsVector.begin(), digitsVector.end()));
    
    // Output the result
    if (validDateCount == 0) 
        cout << "0" << endl;
    else 
        // Format day and month with leading zeros if needed
        printf("%d %02d %02d %04d\n", validDateCount, get<0>(earliestDate), get<1>(earliestDate), get<2>(earliestDate));
}

int main() 
{
    int t;
    string input;
    getline(cin, input);
    istringstream iss(input);
    iss >> t;

    for (int i = 0; i < t && getline(cin, input); i++) 
        solvePokenomDate(input);
    
    return 0;
}

