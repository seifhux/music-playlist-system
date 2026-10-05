/*
سيف حسين محمد ابوالعزايم      20247012
عمر رشاد حسن رشاد              20247008 
*/

#include <iostream>
#include "MusicTrack.h"
using namespace std;

// initialize static variables
int MusicTrack::totalPlaylists = 0;
Song MusicTrack::longestSong = {"", 0.0};


MusicTrack::MusicTrack()
{
    playlist = nullptr;
    playlistSize = 0;
}

MusicTrack::MusicTrack(int size)
{
    playlistSize = size;
    playlist = new Song[playlistSize];
}

MusicTrack::MusicTrack(const MusicTrack &other)
{
    playlistSize = other.playlistSize;
    playlist = new Song[playlistSize];

    for(int i = 0; i < playlistSize; i++)
    {
        playlist[i] = other.playlist[i];
    }

}

void MusicTrack::createPlaylist()
{
    cout << "Enter number of songs: ";
    cin >> playlistSize;
    cin.ignore();

    playlist = new Song[playlistSize];
    
    for(int i = 0; i < playlistSize; i++)
    {
        cout << "Enter song #" << i + 1 << " title: ";
        getline(cin, playlist[i].songTitle);
        cout << "Enter song #" << i + 1 << " duration in minutes: ";
        cin >> playlist[i].songDuration;
        cin.ignore();
        
        if(playlist[i].songDuration > longestSong.songDuration)    // Check and edit variables
        {
            longestSong = playlist[i];
        }
    }
    cout << "Playlist created!" << endl;
    totalPlaylists++;
}

void MusicTrack::addNewSong()
{
    Song *newPlaylist = new Song[playlistSize + 1];     // Create a new dynamic playlist then copy the old data and add the new song
    
    for(int i = 0; i < playlistSize; i++) 
    {
        newPlaylist[i] = playlist[i];
    }

    cout << "Enter song title: ";
    getline(cin, newPlaylist[playlistSize].songTitle);
    cout << "Enter song duration: ";
    cin >> newPlaylist[playlistSize].songDuration;

    if(newPlaylist[playlistSize].songDuration > longestSong.songDuration)   // Check if the added song is longer or not
    { 
        longestSong = newPlaylist[playlistSize];
    }

    cout << "Your song is added successfully!" << endl;

    delete[] playlist;          // delete old playlist
    playlist = newPlaylist;     // makes the pointer points to the new edited playlist
    playlistSize++;             // updates the playlist size

}

MusicTrack::~MusicTrack()
{
    delete[] playlist;  
}

void MusicTrack::removePlaylist()
{
    delete[] playlist;
    playlist = nullptr;       // to reset the pointer
    playlistSize = 0;
    totalPlaylists--;
    cout << "Playlist removed successfully!" << endl;
}

MusicTrack MusicTrack::copyPlaylist()
{   
    MusicTrack newPlaylist(*this);
    totalPlaylists++;
    cout << "Playlist copied successfully!" << endl;

    return newPlaylist;
}

int MusicTrack::totalPlaylistsCreated() {return totalPlaylists;}

Song MusicTrack::getLongestSong() {return longestSong;}

bool MusicTrack::operator>=(const MusicTrack &obj) const
{
    if(playlistSize >= obj.playlistSize) return true;
    else return false;
}

MusicTrack operator+(const MusicTrack& a, const MusicTrack& b)
{
    // First we need to identify the number of common songs to create a playlist with the exact size
    int counter = 0;

    for(int i = 0; i < a.playlistSize; i++)
    {
        for(int j = 0; j < b.playlistSize; j++)
        {
            if(a.playlist[i].songTitle == b.playlist[j].songTitle) counter++;
        }
    }

    MusicTrack commonPlaylist(counter);
    int index = 0; 

    for(int i = 0; i < a.playlistSize; i++)
    {
        for(int j = 0; j < b.playlistSize; j++)
        {
            if(a.playlist[i].songTitle == b.playlist[j].songTitle)
            {
                commonPlaylist.playlist[index] = a.playlist[i];
                index++;
            }
        }
    }

    return commonPlaylist;
}

MusicTrack operator-(const MusicTrack& a, const MusicTrack& b)
{
    // First we need to identify the number of unique songs to create a playlist with the exact size
    int counter = 0;
    bool unique;

    for(int i = 0; i < a.playlistSize; i++)
    {
        unique = true;    // assume true 
        for(int j = 0; j < b.playlistSize; j++)
        {
            if(a.playlist[i].songTitle == b.playlist[j].songTitle) // if unique its okay, if not set bool value to false to make the counter as it was
            {
                unique = false;
                break;
            }
        }

        if(unique) counter++;
    }

    MusicTrack uniquePlaylist(counter);
    int index = 0; 

    for(int i = 0; i < a.playlistSize; i++)
    {
        unique = true;

        for(int j = 0; j < b.playlistSize; j++)
        {
            if(a.playlist[i].songTitle == b.playlist[j].songTitle)
            {
                unique = false;
                break;
            }
        }

        if(unique)
        {
            uniquePlaylist.playlist[index] = a.playlist[i];
            index++;
        }
    }

    return uniquePlaylist;
}

ostream& operator<<(ostream& os, const MusicTrack& other)
{
    for (int i = 0; i < other.playlistSize; i++)
    {
        os << other.playlist[i].songTitle << endl;
    }
    return os;
}

MusicTrack MusicTrack::operator--(int)
{
    Song *newPlaylist = new Song[playlistSize - 1];

    // iterate over the whole playlist and copy it all except the last song
    for(int i = 0; i < playlistSize - 1; i++)
    {
        newPlaylist[i] = playlist[i];
    }

    delete[] playlist;   // delete the old playlist
    playlist = newPlaylist;
    playlistSize--;
    cout << "Last song removed successfully!" << endl;

    return *this;
}

Song MusicTrack::operator[](int index) const
{
    cout << "Song playing: " << playlist[index].songTitle << endl;
    cout << "Song will end in " << playlist[index].songDuration << " minutes." << endl;
    
    return playlist[index];
}

void MusicTrack::printAllSongs() const
{
    cout << "Songs: " << endl;
    cout << *this;
}