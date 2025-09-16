/*
COMSC-210 | Lab 11 | Rylan Der
IDE Used: Visual Studio Code
*/

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<sstream>

using namespace std;

const int IGNORE_CHARS = 100;

struct Song {
    string name;
    int duration; //in seconds
    void Display();
    string GetFormattedDuration();
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

void fillPlaylistlist(Playlist* playlistlist, int size, string filename = "");

void displayPlaylistlist(Playlist* playlistlist, int size);

/**
 * Output a line of chars
 * @param length Length of line
 * @param lineChar Characters composing the line
 */
void CoutLine(int length = 50, char lineChar = '=');

/**
 * @todo Move descriptions to prototypes
 * @todo Test!
 * @todo Add file input
 */
int main() {
    const int SIZE = 2;
    Playlist* playlistlist = nullptr;
    playlistlist = new Playlist[SIZE];
    fillPlaylistlist(playlistlist, SIZE);
    displayPlaylistlist(playlistlist, SIZE);
    delete [] playlistlist;
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
        if (size < 0) {
            cout << "Size must be non-negative" << endl;
        }
    }
    input->ignore(IGNORE_CHARS, '\n'); //ignore after using >>

    //Fill dynamically allocated array of songs
    songs = new Song[size];
    cout << "Entering songs: " << endl;
    for (int i = 0; i < size; i++) {
        cout << " > Enter name of song " << i + 1 << ": " << endl;
        getline(*input, (songs + i)->name);
        while((songs + i)->duration <= 0) { //dont allow durations of 0; duration is 0 by default
            cout << " > Enter duration of song " << i + 1 << " in seconds: " << endl;
            while(!(*input >> (songs + i)->duration)) { 
                cout << "Duration must be an integer" << endl;
                input->clear();
                input->ignore(IGNORE_CHARS, '\n');
            }
            if ((songs + i)->duration <= 0) {
                cout << "Duration must be positive" << endl;
            }
        }
        input->ignore(IGNORE_CHARS, '\n');
    }
} 

void CoutLine(int length, char lineChar) {
    char prevFillChar = cout.fill();
    cout << setw(length) << setfill(lineChar) << "" << setfill(prevFillChar) << endl;
}

/**
 * Output playlist information to console
 * @todo add display function for individual songs, test
 */
void Playlist::Display() {
    CoutLine();
    cout << "Name: " << name << endl;
    cout << "Genre: " << genre << endl;
    cout << "Songs: " << size << endl;
    for (int i = 0; i < size; i++) {
        (songs + i)->Display();
    }
    CoutLine();
}

/**
 * Format song duration in hr:min:seconds format
 * @todo test!
 */
string Song::GetFormattedDuration() {
    stringstream formatted;
    formatted << duration / 3600 << ":"; //hours
    formatted << (duration % 3600) / 60 << ":"; //minutes
    formatted << (duration % 3600) % 60; //seconds
    return formatted.str();
}

/**
 * Output song information to console
 * @todo add formatting to make it look nicer
 */
void Song::Display() {
    cout << "\"" << name << "\": " << GetFormattedDuration() << endl;;
}


/**
 * Fill list of playlists from console or file input
 * @param playlistlist Dynamic array of playlists to fill
 * @param size Size of playlist array
 * @param filename If specified, name of file to retrieve file input from
 * @todo Test!!
 * @todo Add file input
 */
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

/**
 * Output a list of playlists to console output
 * @param playlistlist Dynamic list of playlists to output
 * @param size Size of array of playlists
 * @todo Test: make sure all associated playlist/song display functions work properly
 */
void displayPlaylistlist(Playlist* playlistlist, int size) {
    cout << "Display Playlists" << endl;
    //Calls Display function on each playlist
    //Each playlist will call a song Display function for its songs
    for(int i = 0; i < size; i++) {
        cout << "Playlist #" << i + 1 << ": " << endl;
        (playlistlist + i)->Display();
    }
}
