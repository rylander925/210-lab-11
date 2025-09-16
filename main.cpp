/*
COMSC-210 | Lab 11 | Rylan Der
IDE Used: Visual Studio Code
*/

#include<iostream>
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
    Playlist(): size(0), name(""), genre(""), songs(nullptr) { }
    void Display();
    ~Playlist() {
        if (songs) {
            delete [] songs;
        }
        songs = nullptr;
    }
};

Playlist inputPlaylist();

void fillPlaylistlist(Playlist* playlistlist, int size);

void displayPlaylistlist(Playlist* playlistlist, int size);

int main() {

}

void fillPlaylistlist(Playlist* playlistlist, int size) {
    cout << "Filling playlist list" << endl;
    for(int i = 0; i < size; i++) {
        *(playlistlist + i) = inputPlaylist();
        
    }
}

void displayPlaylistlist(Playlist* playlistlist, int size) {
    cout << "Display Playlists" << endl;
    for(int i = 0; i < size; i++) {
        (playlistlist + i)->Display();
    }
}
