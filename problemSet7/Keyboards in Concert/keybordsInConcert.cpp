
/*
https://open.kattis.com/problems/keyboardconcert
passed all tests!
*/


#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // map each note to the instruments that can play it
    unordered_map<int, vector<int>> note_to_instruments;
    for (int i = 0, numNotes; i < n; i++) 
    {
        cin >> numNotes;
        for (int j = 0, note; j < numNotes; j++) 
        {
            cin >> note;
            note_to_instruments[note].push_back(i); // map `note` value with the instrument's index
        }
    }

    // for (auto i : note_to_instruments)
    // {
    //     auto [note, vec] = i;
    //     cout << "vec indicies that can play note["<<note<<"]: "<<endl;
    //     for (auto v : vec)
    //         cout << v << " ";
        
    //     cout << endl;
    // }
    // cout << endl;

    // sequence of notes
    vector<int> sequence(m);
    for (int i = 0; i < m; i++) 
        cin >> sequence[i];

    // // If any note cannot be played by any instrument, output -1
    // for (int note : sequence) {
    //     if (note_to_instruments.find(note) == note_to_instruments.end()) {
    //         cout << -1 << endl;
    //         return 0;
    //     }
    // }

    // Greedy approach to minimize switches
    int switches = 0;
    int current_instrument = -1;

    for (int i = 0; i < m;) 
    {
        // find the instrument that can play the longest subsequence starting from note i
        int max_length = 0;
        int best_instrument = -1;

        // Try all instruments that can play the current note
        for (int instr : note_to_instruments[sequence[i]]) 
        {
            int length = 0;
            // check how many consecutive `notes` this instrument can play
            while (i + length < m && find(note_to_instruments[sequence[i + length]].begin(), note_to_instruments[sequence[i + length]].end(), instr) != note_to_instruments[sequence[i + length]].end()) 
                length++;
            
            // update the best instrument
            if (length > max_length) 
            {
                max_length = length;
                best_instrument = instr;
            }
        }

        // // If no instrument can play the current note, output -1
        // if (best_instrument == -1) {
        //     cout << -1 << endl;
        //     return 0;
        // }

        // switch to the best instrument
        if (best_instrument != current_instrument) 
        {
            switches++;
            current_instrument = best_instrument;
        }

        // move to the next note after the longest subsequence
        i += max_length;
    }

    cout << (switches - 1 == -1 ? 0 : switches - 1) << endl;    // Subtract 1 because the first instrument doesn't count as a switch
    return 0;
}
