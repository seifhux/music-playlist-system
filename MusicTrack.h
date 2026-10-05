/*
سيف حسين محمد ابوالعزايم      20247012
عمر رشاد حسن رشاد              20247008 
*/
#pragma once
#include "Song.h"

class MusicTrack{
    private:
        Song *playlist;
        int playlistSize;
        static int totalPlaylists;
        static Song longestSong;

    public:
        MusicTrack();
        MusicTrack(int size);
        MusicTrack(const MusicTrack &other);
        ~MusicTrack();
        void createPlaylist();
        void addNewSong();
        void removePlaylist();
        MusicTrack copyPlaylist();
        static int totalPlaylistsCreated();
        static Song getLongestSong();
        bool operator>=(const MusicTrack &obj) const;
        friend MusicTrack operator+(const MusicTrack& a, const MusicTrack& b);
        friend MusicTrack operator-(const MusicTrack& a, const MusicTrack& b);
        MusicTrack  operator--(int);
        Song operator[](int index) const;
        friend ostream& operator<<( ostream& os, const MusicTrack& other);
        int getPlaylistSize() const {return playlistSize;}
        Song *getPlaylist() const {return playlist;}
        void printAllSongs() const;
};


