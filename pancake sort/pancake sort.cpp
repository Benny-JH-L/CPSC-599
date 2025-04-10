
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void print_vec(vector<int>& v)
{
    for (auto& e : v)
        cout << e << ", ";
    cout << endl;
}

int find_largest_pancake(vector<int>& pancake_stack, int end)
{
    auto largest_pancake = max_element(pancake_stack.begin(), pancake_stack.begin() + end);
    return distance(pancake_stack.begin(), largest_pancake);    // return index of where pancake is located
}

void flip(vector<int>& pancake_stack, int k)
{
    reverse(pancake_stack.begin(), pancake_stack.begin() + k);
}

void pancake_sort(vector<int>& pancake_stack)
{
    int n = pancake_stack.size();
    
    for (int curr_size = n; curr_size > 1; curr_size--)
    {
        // Step 1, find largest pancake
        int largest_pancake_idx = find_largest_pancake(pancake_stack, curr_size);

        // If the largest isn't already at the bottom of the unsorted section
        if (largest_pancake_idx != curr_size - 1)
        {
            // Step 2, flip the stack so the pancake is on top
            if (largest_pancake_idx != 0)
            {
                flip(pancake_stack, largest_pancake_idx + 1);
                cout << "Fliped at idx: " << largest_pancake_idx << ": ";
            }

            // Step 3, flip unsorted potion so pancake is now sorted
            flip(pancake_stack, curr_size);
            cout << "Fliped at idx: " << curr_size - 1 << ": ";
        }
        // Step 4, repeat until you've gone through the whole stack
    }
}

int main()
{
    vector<int> v1 = {5, 4, 3, 2, 1};
    // print_vec(v1);
    // reverse(v1.begin(), v1.end());
    // print_vec(v1);
    // reverse(v1.begin(), v1.begin() + 2);
    // print_vec(v1);

    v1 = {4, 5, 1, 2, 3};
    print_vec(v1);
    pancake_sort(v1);
    print_vec(v1);
    return 0;
}


void pancake_sort_debug(vector<int>& pancake_stack)
{
    int n = pancake_stack.size();
    
    for (int curr_size = n; curr_size > 1; curr_size--)
    {
        // Step 1, find largest pancake
        int largest_pancake_idx = find_largest_pancake(pancake_stack, curr_size);

        // If the largest isn't already at the bottom of the unsorted section
        if (largest_pancake_idx != curr_size - 1)
        {
            // Step 2, flip the stack so the pancake is on top
            if (largest_pancake_idx != 0)
            {
                flip(pancake_stack, largest_pancake_idx + 1);
                cout << "Fliped at idx: " << largest_pancake_idx << ": ";
                print_vec(pancake_stack);
            }

            // Step 3, flip unsorted potion so pancake is now sorted
            flip(pancake_stack, curr_size);
            cout << "Fliped at idx: " << curr_size - 1 << ": ";
            print_vec(pancake_stack);
        }
        // Step 4, repeat until you've gone through the whole stack
    }
}
