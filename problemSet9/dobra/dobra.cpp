
/*
https://ucalgary.kattis.com/courses/CPSC_599-4/Winter_2025/assignments/bcty6b/problems/dobra
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

bool isVowel(char c) 
{
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

// States: position, consecutive vowels, consecutive consonants, has 'L'
// Memoization to avoid recalculating the same states
map<tuple<int, int, int, bool>, long long> memo;

// Recursive function with memoization
long long countWords(const string& word, int pos, int consVowels, int consCons, bool hasL) 
{
    // Base case: all characters are processed
    if (pos == word.length()) 
        return (hasL) ? 1 : 0;
    
    // Check if this state has already been calculated
    tuple<int, int, int, bool> state = make_tuple(pos, consVowels, consCons, hasL);
    if (memo.find(state) != memo.end()) 
        return memo[state];
    
    long long count = 0;
    
    // If current position is not an underscore
    if (word[pos] != '_') 
    {
        char c = word[pos];
        bool isV = isVowel(c);
        bool newHasL = hasL || (c == 'L');
        
        // Calculate new consecutive counters
        int newConsVowels = isV ? consVowels + 1 : 0;
        int newConsCons = isV ? 0 : consCons + 1;
        
        // Check if this character causes a violation
        if (newConsVowels >= 3 || newConsCons >= 3) 
            return 0;
        
        count = countWords(word, pos + 1, newConsVowels, newConsCons, newHasL);
    } 
    // If current position is an underscore
    else 
    {
        // Try each possible letter (A-Z)
        for (char c = 'A'; c <= 'Z'; c++) 
        {
            bool isV = isVowel(c);
            bool newHasL = hasL || (c == 'L');
            
            // Calculate new consecutive counters
            int newConsVowels = isV ? consVowels + 1 : 0;
            int newConsCons = isV ? 0 : consCons + 1;
            
            // Skip if this character causes a violation
            if (newConsVowels >= 3 || newConsCons >= 3) 
                continue;
            
            count += countWords(word, pos + 1, newConsVowels, newConsCons, newHasL);
        }
    }
    
    // Save result in memo and return
    memo[state] = count;
    return count;
}

int main() 
{
    string word;
    cin >> word;
    
    memo.clear();
    long long result = countWords(word, 0, 0, 0, false);
    cout << result << endl;
    
    return 0;
}

