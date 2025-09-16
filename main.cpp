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
    Playlist();
    int size;
    string name;
    string genre;
    Song* songs;
    ~Playlist() {
        if (songs) {
            delete [] songs;
        }
        songs = nullptr;
    }
};

void fillPlaylistlist(Playlist* playlistlist);

void displayPlaylistlist(Playlist* playlistlist);

int main() {

}

