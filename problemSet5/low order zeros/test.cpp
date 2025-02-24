#include <iostream>
using namespace std;

int lastNonZeroDigit(int n) {
    int result = 1;
    int count_five = 0;

    for (int i = 1; i <= n; i++) {
        int num = i;
        
        // Remove factors of 5 and count them
        while (num % 5 == 0) {
            num /= 5;
            count_five++;
        }
        
        // Remove factors of 2 to balance the 5s counted earlier
        while (num % 2 == 0 && count_five > 0) {
            num /= 2;
            count_five--;
        }
        
        // Multiply the number to result and keep only the last nonzero digit
        result = (result * num) % 10;
    }
    
    // Restore remaining 5s
    for (int i = 0; i < count_five; i++) {
        result = (result * 5) % 10;
    }
    
    return result;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;
    cout << "The last nonzero digit of " << n << "! is " << lastNonZeroDigit(n) << endl;
    return 0;
}
