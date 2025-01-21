
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/b7bqkq/problems/birthdayboy
*/

#include <stdio.h>
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
    // testing
    string test = "09-19";
    int month, day;

    istringstream iss(test);
    char separater;
    iss >> month >> separater >> day;

    cout << "Month: " << month << " | Day: " << day << endl;

    


    return 0;
}
