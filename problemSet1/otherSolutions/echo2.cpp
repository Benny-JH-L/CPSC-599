
#include <iostream>
using namespace std;

int main()
{
    string word;
    cout << "enter word: ";
    cin >> word;

    string echo;
    for (int i = 0; i < 3; i++)
        echo += word + " ";
    cout << echo << endl;
}
