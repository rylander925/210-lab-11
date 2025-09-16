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
    Song(string name, int duration): name(name), duration(duration) { }
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

int main() {
}

void Playlist::Fill(istream* input) {
    cout << "Enter name: " << endl;
    getline(*input, name);
    cout << "Enter genre: " << endl;
    getline(*input, genre);
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

    songs = new Song[size];
    cout << "Entering songs: " << endl;
    for (int i = 0; i < size; i++) {
        cout << " > Enter song name: " << endl;
        getline(*input, name);
        while(size <= 0) { //dont allow durations of 0; duration is 0 by default
            cout << " > Enter song duration in seconds: " << endl;
            while(!(*input >> size)) { 
                cout << "Duration must be an integer" << endl;
                input->clear();
                input->ignore(IGNORE_CHARS, '\n');
            }
            cout << "Duration must be positive" << endl;
        }
        
    }

    

} 

void Playlist::Display() {

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
        (playlistlist + i)->Display();
    }
}
