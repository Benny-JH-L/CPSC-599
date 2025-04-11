
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() 
{
    string prev_animal;
    cin >> prev_animal;
    
    int n;
    cin >> n;
    
    vector<string> valid_animals(n);
    for (int i = 0; i < n; i++)
        cin >> valid_animals[i];
    
    char last_letter = prev_animal[prev_animal.length() - 1];
    
    for (const string& animal : valid_animals) 
    {
        if (animal[0] == last_letter) 
        {
            char next_last_letter = animal[animal.length() - 1];
            bool eliminates_next = true;
            
            for (const string& next_animal : valid_animals) 
            {
                if (next_animal != animal && next_animal[0] == next_last_letter) 
                {
                    eliminates_next = false;
                    break;
                }
            }
            
            if (eliminates_next) 
            {
                cout << animal << "!" << endl;
                return 0;
            }
        }
    }
    
    for (const string& animal : valid_animals) 
    {
        if (animal[0] == last_letter) 
        {
            cout << animal << endl;
            return 0;
        }
    }
    
    cout << "?" << endl;
    
    return 0;
}
