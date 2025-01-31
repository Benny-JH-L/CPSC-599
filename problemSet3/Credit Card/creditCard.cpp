
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

// there is prolly some rounding error happening?
// maybe submit again, because before i forgot to increment counter after each tes case

int main()
{
    // double v1 = 5462.505;
    // // printf("%3.f\n", v1); // dont work
    // cout << "Before round: " << v1 << endl;
    // roundThing(v1, 3);
    // cout << "After round: " << v1 << endl;
    // // printf("%3.f\n", v1); // dont work
    // v1 = 3.14159;
    // // printf("%3.f\n", roundThing(v1,3)); // dont work
    // cout << roundThing(v1, 3) << endl;


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
        // cout << intererstRate << endl;
        // cout << outstandingBalance << endl;
        // cout << monthlyPayment << endl;

        // cout << "before round interest rate: " <<  interestAmount << endl;
        // cout << "after round interest rate: " <<  myRound(interestAmount, 2) << endl;

        if (monthlyPayment > (outstandingBalance + myRound(interestAmount, 2)))    // not equal since interest will be applied to balance first
        {
            outputVector.push_back(1);   // if monthly payment > (outgoing balace + intrest) -> 1 payment needed
            continue;
        }
        else
        {
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
            for (int numberOfPayments = 0; numberOfPayments < 1200; numberOfPayments++)
            {
                interestAmount = outstandingBalance * (intererstRate / 100.f);  

                // cout << "before round interest rate: " <<  interestAmount << endl;
                myRound(interestAmount, 2); // need to round half cents up to the nearerst cent
                // cout << "after round interest rate: " <<  interestAmount << endl;
                
                outstandingBalance += interestAmount;   // add interst first
                outstandingBalance -= monthlyPayment;   // then subtract monthly payment
                // myRound(outstandingBalance, 2); // maybe?

                if (outstandingBalance <= 0)
                {
                    outputVector.push_back(numberOfPayments + 1);   // add 1 since we start at 0
                    break;
                }
                else if (numberOfPayments + 1 >= 1200)
                {
                    outputVector.push_back(-1);
                    // cout << "number of payments before we find it as impossible: " << numberOfPayments << endl; // debug
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
