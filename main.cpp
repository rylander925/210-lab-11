/*
COMSC-210 | Lab 11 | Rylan Der
IDE Used: Visual Studio Code
*/

#include<iostream>
#include <string>
#include<fstream>

using namespace std;

const int IGNORE_CHARS = 100;

struct Song {
    string name;
    int duration; //in seconds
    Song(): name(""), duration(0) { };
};

struct Playlist {
    int size;
    string name;
    string genre;
    Song* songs;
    Playlist(): size(-1), name(""), genre(""), songs(nullptr) { }
    void Fill(istream* input);
    void Display();
    ~Playlist() {
        if (songs) {
            delete [] songs;
        }
        songs = nullptr;
    }
};

void fillPlaylistlist(Playlist* playlistlist, int size, string filename);

void displayPlaylistlist(Playlist* playlistlist, int size);

/**
 * Output a line of chars
 * @param length Length of line
 * @param lineChar Characters composing the line
 */
void CoutLine(int length = 50, char lineChar = '=');

int main() {
}

/**
 * Fill a playlist from input
 * @param input Pointer to an istream object to take input from
 * @todo TEST!!
 */
void Playlist::Fill(istream* input) {
    //Get playlist details from input
    cout << "Enter name: " << endl;
    getline(*input, name);
    cout << "Enter genre: " << endl;
    getline(*input, genre);

    //Use input validation for playlist size
    while(size < 0) { //allow empty playlists, size is -1 by default
        cout << "Enter playlist size: " << endl;
        while(!(*input >> size)) { 
            cout << "Size must be an integer" << endl;
            input->clear();
            input->ignore(IGNORE_CHARS, '\n');
        }
        cout << "Size must be non-negative" << endl;
    }
    input->ignore(IGNORE_CHARS, '\n'); //ignore after using >>

    //Fill dynamically allocated array of songs
    songs = new Song[size];
    cout << "Entering songs: " << endl;
    for (int i = 0; i < size; i++) {
        cout << " > Enter song name: " << endl;
        getline(*input, (songs + i)->name);
        while((songs + i)->duration <= 0) { //dont allow durations of 0; duration is 0 by default
            cout << " > Enter song duration in seconds: " << endl;
            while(!(*input >> (songs + i)->duration)) { 
                cout << "Duration must be an integer" << endl;
                input->clear();
                input->ignore(IGNORE_CHARS, '\n');
            }
            cout << "Duration must be positive" << endl;
        }
    }
    input->ignore(IGNORE_CHARS, '\n');
} 

void CoutLine(int length) {

}

void Playlist::Display() {
    cout << ""

}

void fillPlaylistlist(Playlist* playlistlist, int size, string filename) {
    istream* input;
    //TODO: Add file input
    input = &cin;
    cout << "Filling playlist list" << endl;
    for(int i = 0; i < size; i++) {
        cout << "Playlist #" << i + 1 << ":" << endl;
        (playlistlist + i)->Fill(input);
        
    }
}

void displayPlaylistlist(Playlist* playlistlist, int size) {
    cout << "Display Playlists" << endl;
    for(int i = 0; i < size; i++) {
        cout << "Playlist #" << i + 1 << ": " << endl;
        (playlistlist + i)->Display();
    }
}
