
/*
Question:
A Metronome is a mechanical device used by musicians for keeping time. It is a very clever device, 
based on a spring, an inverted pendulum, and an escapement gear. 
Milo is learning to play the glockenspiel, and has purchased a metronome to help him keep time. 
Milo has noticed that for every complete turn (one revolution) of the key, the metronome will give four ticks. 
Milo wants the metronome to stop at the end of each song that he tries to play.
For a given song, how many revolutions must he wind the key?
*/

// 4 instrument ticks for 1
// full revolution of the key.
// input is a song in number of ticks

#include <iostream>
using namespace std;

int main()
{
    float songLen;
    cout << "song length: ";
    cin >> songLen;
    cout << "Revolutions: " << songLen/4 << endl;
}
