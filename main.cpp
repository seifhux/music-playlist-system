/*
سيف حسين محمد ابوالعزايم      20247012
عمر رشاد حسن رشاد             20247008 
*/

#include <iostream>
#include "MusicTrack.h"
#include <vector>
using namespace std;


void printMenu()
{
    cout << "\n\tSYSTEM MAIN MENU" << endl
            << "\t================" << endl
            << "[01] Create a new playlist" << endl 
            << "[02] Add new songs to a playlist" << endl
            << "[03] Remove a playlist" << endl
            << "[04] Copy a playlist" << endl
            << "[05] Display total playlists created" << endl
            << "[06] Show the longest song among all playlists" << endl
            << "[07] Compare two playlists" << endl
            << "[08] Play a song by index" << endl
            << "[09] Display common songs" << endl
            << "[10] Display unique songs" << endl
            << "[11] Remove last song" << endl
            << "[12] Print all songs" << endl
            << "[13] Exit" << endl
            << "Pick an option: ";
}


int main()
{
    vector<MusicTrack> allPlaylists;
    int currentPlaylist;

    while(true)
    {
        printMenu();
        int userChoice = 0;
        cin >> userChoice;
        
        switch (userChoice)
        {
            case 1:
            {
                MusicTrack playlist;
                playlist.createPlaylist();   
                allPlaylists.push_back(playlist);
                currentPlaylist = allPlaylists.size() - 1;
                break;
            }

            case 2:
            {
                allPlaylists[currentPlaylist].addNewSong();
                break;    
            }    
            
            case 3:
            {
                int playlistNum, index;
                cout << "Enter playlist number you want to remove: ";
                cin >> playlistNum;
                index = playlistNum - 1;
                
                allPlaylists[index].removePlaylist();
                allPlaylists.erase(allPlaylists.begin() + index);

                if(currentPlaylist == index) currentPlaylist = -1;
                else if(currentPlaylist > index) currentPlaylist--;
                break;
            }

            case 4:
            {
                int playlistNum, index;
                cout << "Enter playlist number you want to copy: ";
                cin >> playlistNum;
                index = playlistNum - 1;

                MusicTrack copiedPlaylist = allPlaylists[index].copyPlaylist();
                allPlaylists.push_back(copiedPlaylist);
                break;
            }
             
            case 5:
            {
                cout << "Total playlists: " << MusicTrack::totalPlaylistsCreated() << endl;
                break;
            }

            case 6:
            {
                Song longest = MusicTrack::getLongestSong();

                cout << "Longest song: " << longest.songTitle << endl;
                cout << "Duration: " << longest.songDuration << " minutes" << endl;
                break;
            }
            
            case 7:
            {
                int playlistNum1, playlistNum2, index1, index2;
                cout << "Enter first playlist number: ";
                cin >> playlistNum1;
                index1 = playlistNum1 - 1;
                cout << "Enter second playlist number: ";
                cin >> playlistNum2;
                index2 = playlistNum2 - 1; 
                
                if(allPlaylists[index1] >= allPlaylists[index2]) cout << "Playlist #" << playlistNum1 << " is greater than or equal playlist #" << playlistNum2 << endl;
                else cout << "Playlist #" << playlistNum2 << " is greater than or equal playlist #" << playlistNum1 << endl;
                break;    
            }

            case 8:
            {
                int playlistNum, songNum, playlistIndex, songIndex;
                cout << "Enter playlist number: ";
                cin >> playlistNum;
                playlistIndex = playlistNum - 1;
                cout << "Enter song number: ";
                cin >> songNum;
                songIndex = songNum - 1;

                Song nowPlaying = allPlaylists[playlistIndex][songIndex];
                break;
            }

            case 9:
            {
                int playlistNum1, playlistNum2, index1, index2;
                cout << "Enter first playlist number: ";
                cin >> playlistNum1;
                index1 = playlistNum1 - 1;
                cout << "Enter second playlist number: ";
                cin >> playlistNum2;
                index2 = playlistNum2 - 1;
                
                MusicTrack commonPlaylist = allPlaylists[index1] + allPlaylists[index2];
                cout << "Common songs: " << endl;
                cout << commonPlaylist;
                break;
            }

            case 10:
            {
                int playlistNum1, playlistNum2, index1, index2;
                cout << "Enter first playlist number: ";
                cin >> playlistNum1;
                index1 = playlistNum1 - 1;
                cout << "Enter second playlist number: ";
                cin >> playlistNum2;
                index2 = playlistNum2 - 1;
                
                MusicTrack uniquePlaylist = allPlaylists[index1] - allPlaylists[index2];
                cout << "Unique songs: " << endl;
                cout << uniquePlaylist;
                break;    
            }

            case 11:
            {
                int playlistNum, index;
                cout << "Enter playlist number you want to remove its last song: ";
                cin >> playlistNum;
                index = playlistNum - 1;
                
                allPlaylists[index]--;
                break;
            }

            case 12:
            {
                int playlistNum, index;
                cout << "Enter playlist number you want to display: ";
                cin >> playlistNum;
                index = playlistNum - 1;
                
                allPlaylists[index].printAllSongs();
                break;
            }

            case 13:
            {
                cout << "Program ending." << endl;
                return 0;
            }

            default:
            {
                cout << "Invalid option. Try again." << endl;
                break;    
            }
        }
    }
}