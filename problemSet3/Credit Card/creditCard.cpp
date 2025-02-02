
/*
https://open.kattis.com/problems/creditcard
Passed all tests!
*/

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

double myRound(double& val, int decimalPlaces)
{
    double scale = pow(10, decimalPlaces);
    double rounded = round(val * scale) / scale;
    val = rounded;
    return rounded;
}

int main()
{
    string input;
    getline(cin, input);
    istringstream iss(input);
    int numTests = 0, counter = 0;
    iss >> numTests;

    vector<int> outputVector;
    // go through each test case
    while (counter < numTests && getline(cin, input) && input != "")
    {
        double intererstRate, outstandingBalance, monthlyPayment;
        iss = istringstream(input);
        iss >> intererstRate >> outstandingBalance >> monthlyPayment;
        double interestAmount = outstandingBalance * (intererstRate / 100.f);  // convert from rate (%) to decimal

        // debug
        // cout << "interest rate: " << intererstRate << "%" << endl;
        // cout << outstandingBalance << endl;
        // cout << monthlyPayment << endl;

        // cout << "before round interest rate: " <<  interestAmount << endl;
        // cout << "after round interest rate: " <<  myRound(interestAmount, 2) << endl;

        if (monthlyPayment > (outstandingBalance + myRound(interestAmount, 2)))    // not equal since interest will be applied to balance first
        {
            outputVector.push_back(1);   // if monthly payment > (outgoing balace + intrest) -> 1 payment needed
            counter++;
            continue;
        }
        else
        {
            for (int numberOfPayments = 0; numberOfPayments < 1200; numberOfPayments++)
            {
                interestAmount = outstandingBalance * (intererstRate / 100);  
                interestAmount = round(interestAmount * 100) / 100; // need to round half cents up to the nearerst cent 
                
                outstandingBalance += interestAmount;   // add interst first
                outstandingBalance = round(outstandingBalance * 100) / 100;
                outstandingBalance -= monthlyPayment;   // then subtract monthly payment

                if (outstandingBalance <= 0)
                {
                    outputVector.push_back(numberOfPayments + 1);   // add 1 since we start at 0
                    break;
                }
                else if (numberOfPayments + 1 >= 1200)
                {
                    outputVector.push_back(-1);
                    // cout << "number of payments before we find it as impossible: " << numberOfPayments + 1 << endl; // debug
                    // cout << "remaining balance: " << outstandingBalance << endl;    //debug
                    break;
                }
            }
        }
        counter++;
    }

    for (int result : outputVector)
        cout << (result == -1 ? "impossible" : to_string(result)) << endl;

    return 0;
}

            // for (int numberOfPayments = 1; numberOfPayments < 1201; numberOfPayments++)
            // {
            //     interestAmount = outstandingBalance * (intererstRate / 100.f);  

            //     // cout << "before round interest rate: " <<  interestAmount << endl;
            //     myRound(interestAmount, 2); // need to round half cents up to the nearerst cent
            //     // cout << "after round interest rate: " <<  interestAmount << endl;
                
            //     outstandingBalance += interestAmount;   // add interst first
            //     outstandingBalance -= monthlyPayment;   // then subtract monthly payment
            //     // myRound(outstandingBalance, 2); // maybe?

            //     if (outstandingBalance <= 0)
            //     {
            //         outputVector.push_back(numberOfPayments);
            //         break;
            //     }
            //     else if (numberOfPayments + 1 >= 1201)
            //     {
            //         outputVector.push_back(-1);
            //         cout << "number of payments before we find it as impossible: " << numberOfPayments << endl; // debug
            //         break;
            //     }
            // }
