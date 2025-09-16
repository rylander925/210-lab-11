/*
COMSC-210 | Lab 11 | Rylan Der
IDE Used: Visual Studio Code
*/

#include<iostream>
#include <string>
#include<fstream>

using namespace std;

struct Song {
    string name;
    int duration; //in seconds
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
    cout << "Enter playlist size: " << endl;
    while(size < 0) { //allow empty playlists, size is -1 by default
        while(!(*input >> size)) { 
            cout << "Size must be an integer" << endl;
            input->clear();
            input->ignore(100, '\n');
        }
        cout << "Size must be non-negative" << endl;
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
