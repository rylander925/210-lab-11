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

struct Song {
    string name;
    string artist;
    int duration; //in seconds
    Song(): name(""), duration(0), artist("") { };
};

struct Playlist {
    const static int TABLE_PADDING = 5;
    int size;
    string name;
    string genre;
    Song* songs;
    int tableSongWidth;
    int tableDurationWidth;
    int totalDuration;

    Playlist(): size(-1), name(""), genre(""), songs(nullptr), tableSongWidth(50), tableDurationWidth(10), totalDuration(0) { }

    /**
     * Fill a playlist from input
     * @param input Pointer to an istream object to take input from
     */
    void Fill(istream* input);

    /**
     * Output playlist information to console
     */
    void Display();

    ~Playlist() {
        if (songs) {
            delete [] songs;
        }
        songs = nullptr;
    }
};

/**
 * Format a given time in seconds as HRhr MINmin SECsec
 * @param seconds Time to be formatted
 * @return String text of formatted duration
 */
string FormatDuration(int seconds);

/**
 * Fill list of playlists from console or file input
 * @param playlistlist Dynamic array of playlists to fill
 * @param size Size of playlist array
 * @param filename If specified, name of file to retrieve file input from
 */
void fillPlaylistlist(Playlist* playlistlist, int size, string filename = "");

/**
 * Output a list of playlists to console output
 * @param playlistlist Dynamic list of playlists to output
 * @param size Size of array of playlists
 * @todo Test: make sure all associated playlist/song display functions work properly
 */
void displayPlaylistlist(Playlist* playlistlist, int size);

/**
 * Output a line of chars
 * @param length Length of line
 * @param lineChar Characters composing the line
 */
void CoutLine(int length = 60, char lineChar = '=');

int main() {
    const int SIZE = 3;
    const string FILENAME = "data.txt";

    //allocate memory to array of playlists
    Playlist* playlistlist = nullptr;
    playlistlist = new Playlist[SIZE];

    fillPlaylistlist(playlistlist, SIZE);
    displayPlaylistlist(playlistlist, SIZE);

    delete [] playlistlist;
}

void Playlist::Fill(istream* input) {
    const static int IGNORE_CHARS = 100;
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
        cout << " >> Enter artist name: " << endl;
        getline(*input, (songs + i)->artist);

        //save longest song so display table formats properly
        int songWidth = (songs + i)->name.size() + (songs + i)->artist.size() + TABLE_PADDING;
        tableSongWidth = (tableSongWidth < songWidth) ?  songWidth : tableSongWidth;

        //get song duration w/ input validation
        while((songs + i)->duration <= 0) { //dont allow durations of 0; duration is 0 by default
            cout << " >> Enter duration of song " << i + 1 << " in seconds: " << endl;
            while(!(*input >> (songs + i)->duration)) { 
                cout << " >>> Duration must be an integer" << endl;
                input->clear();
                input->ignore(IGNORE_CHARS, '\n');
            }
            if ((songs + i)->duration <= 0) {
                cout << " >>> Duration must be positive" << endl;
            }
        }
        input->ignore(IGNORE_CHARS, '\n');
        
        //save duration of entire playlist
        totalDuration += (songs + i)->duration;

        //save longest duration width so display table formats properly
        int durationWidth = FormatDuration((songs + i)->duration).size();
        tableDurationWidth = (tableDurationWidth < durationWidth) ? durationWidth : tableDurationWidth; 
    }
} 

void CoutLine(int length, char lineChar) {
    char prevFillChar = cout.fill();
    cout << setw(length) << setfill(lineChar) << "" << setfill(prevFillChar) << endl;
}

void Playlist::Display() {
    //Display playlist info
    CoutLine(tableSongWidth + tableDurationWidth);
    cout << "Name: " << name << endl;
    cout << "Genre: " << genre << endl;
    cout << "Songs: " << size << endl;
    cout << "Duration: " << FormatDuration(totalDuration) << endl;

    //Display formatted table of songs
    CoutLine(tableSongWidth + tableDurationWidth);
    cout << setw(tableSongWidth) << left << "Song Name and Artist"
         << setw(tableDurationWidth) << "Duration" << endl;
    CoutLine(tableSongWidth + tableDurationWidth, '-');
    for (int i = 0; i < size; i++) {
        cout << setw(tableSongWidth) << (songs + i)->name + " by " + (songs + i)->artist
             << setw(tableDurationWidth) << FormatDuration((songs + i)->duration) << endl;
    }
    CoutLine(tableDurationWidth+tableSongWidth);
}

string FormatDuration(int seconds) {
    stringstream formatted;
    if (seconds >= 3600) {
        formatted << seconds / 3600 << "hr "; //hours
    }
    if (seconds >= 60) {
        formatted << (seconds % 3600) / 60 << "min "; //minutes
    }
    formatted << (seconds % 3600) % 60 <<"s "; //seconds
    return formatted.str();
}

void fillPlaylistlist(Playlist* playlistlist, int size, string filename) {
    //choose between console or file input
    istream* input;
    ifstream infile;
    if (filename != "") {
        infile.open(filename);
        //verify file opens properly
        if (!infile.good()) {
            cout << "ERROR: Failed to open file \"" << filename << "\"" << endl;
            throw ios_base::failure("Invalid file name");
        }
        input = &infile;
    } else {
        input = &cin;
    }

    //Calls fill function of each playlist
    cout << "Filling playlist list" << endl;
    for(int i = 0; i < size; i++) {
        cout << "Playlist #" << i + 1 << ":" << endl;
        (playlistlist + i)->Fill(input);
        
    }

    if(infile.is_open()) {
        infile.close();
    }
}

void displayPlaylistlist(Playlist* playlistlist, int size) {
    CoutLine();
    cout << "Displaying Playlists" << endl;
    CoutLine();
    //Calls Display function of each playlist
    for(int i = 0; i < size; i++) {
        cout << "Playlist #" << i + 1 << ": " << endl;
        (playlistlist + i)->Display();
    }
}
