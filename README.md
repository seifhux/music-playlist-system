# Music Playlist Management System

A console-based music playlist manager written in **C++**. It lets you create playlists, add and remove songs, copy and delete playlists, and compare them with set-style operations, all through a simple numbered menu.

The project is built around a custom `MusicTrack` class that manages a **dynamically allocated array** of songs and makes heavy use of **operator overloading**, so playlists can be compared, combined, indexed, and printed with natural syntax.

This was developed as a university coursework project at Cairo University, Faculty of Computer Science and Artificial Intelligence (FCAI).

---

## Table of Contents

- [Features](#features)
- [Concepts Demonstrated](#concepts-demonstrated)
- [Project Structure](#project-structure)
- [Design Overview](#design-overview)
- [Operator Overloading Reference](#operator-overloading-reference)
- [Build and Run](#build-and-run)
- [Usage Guide](#usage-guide)
- [Example Session](#example-session)
- [Known Limitations](#known-limitations)
- [Possible Improvements](#possible-improvements)
- [Authors](#authors)

---

## Features

- **Create playlists** by entering a number of songs, then a title and duration (in minutes) for each one.
- **Add songs** to the current playlist at any time. The underlying array is resized automatically.
- **Remove a playlist** and free its memory.
- **Copy a playlist** into a new, independent playlist (deep copy).
- **Track statistics across all playlists**, including the total number of playlists and the longest song ever entered.
- **Compare two playlists** by size.
- **Play a song by index**, which shows the song title and how many minutes remain.
- **Find common songs** between two playlists.
- **Find unique songs** that appear in one playlist but not the other.
- **Remove the last song** from a playlist.
- **Print all songs** in a playlist.

---

## Concepts Demonstrated

- Classes, encapsulation, and `private` / `public` access control
- Dynamic memory allocation with `new[]` and `delete[]`
- Constructors (default, parameterized, and copy), and a destructor
- Deep copying of dynamically allocated data
- Operator overloading as member functions and as `friend` functions
- Static data members and static member functions
- Returning objects by value
- Use of `std::vector` to store multiple playlist objects
- Header and source file separation with `#pragma once`
- Menu-driven console application design with `switch`

---

## Project Structure

```
.
├── Song.h          # Song struct (title + duration)
├── MusicTrack.h    # MusicTrack class declaration
├── MusicTrack.cpp  # MusicTrack class implementation and operator definitions
└── main.cpp        # Menu-driven program entry point
```

| File | Responsibility |
|------|----------------|
| `Song.h` | Defines the `Song` struct with `songTitle` (`string`) and `songDuration` (`double`, in minutes). |
| `MusicTrack.h` | Declares the `MusicTrack` class: its data members, constructors, destructor, methods, and overloaded operators. |
| `MusicTrack.cpp` | Implements everything declared in `MusicTrack.h` and initializes the static members. |
| `main.cpp` | Holds a `vector<MusicTrack>` of all playlists, prints the main menu, and dispatches each choice to the right `MusicTrack` function or operator. |

---

## Design Overview

### The `Song` struct

```cpp
struct Song
{
    string songTitle;
    double songDuration;
};
```

### The `MusicTrack` class

Each `MusicTrack` object represents one playlist.

**Instance data**

| Member | Type | Description |
|--------|------|-------------|
| `playlist` | `Song*` | Pointer to a dynamically allocated array of songs. |
| `playlistSize` | `int` | Number of songs currently in the playlist. |

**Static data (shared by all playlists)**

| Member | Type | Description |
|--------|------|-------------|
| `totalPlaylists` | `int` | Number of playlists currently existing in the system. |
| `longestSong` | `Song` | The longest song entered across all playlists. |

**Constructors and destructor**

| Function | Purpose |
|----------|---------|
| `MusicTrack()` | Creates an empty playlist (`nullptr`, size 0). |
| `MusicTrack(int size)` | Allocates room for `size` songs. Used internally when building the results of `+` and `-`. |
| `MusicTrack(const MusicTrack&)` | Copy constructor that performs a **deep copy** of the song array. |
| `~MusicTrack()` | Releases the dynamic array with `delete[]`. |

**Member functions**

| Function | Description |
|----------|-------------|
| `createPlaylist()` | Prompts for the number of songs and their details, updates the longest song, and increments the playlist counter. |
| `addNewSong()` | Allocates a new array one element larger, copies the old songs, appends the new one, frees the old array, and updates the longest song if needed. |
| `removePlaylist()` | Frees the array, resets the pointer and size, and decrements the playlist counter. |
| `copyPlaylist()` | Returns a deep copy of the playlist and increments the playlist counter. |
| `printAllSongs()` | Prints every song title using the overloaded `<<` operator. |
| `getPlaylistSize()` / `getPlaylist()` | Simple inline getters. |
| `totalPlaylistsCreated()` *(static)* | Returns the playlist counter. |
| `getLongestSong()` *(static)* | Returns the longest song recorded so far. |

---

## Operator Overloading Reference

| Operator | Kind | Usage in `main.cpp` | What it does |
|----------|------|---------------------|--------------|
| `>=` | Member | `a >= b` | Returns `true` if playlist `a` has at least as many songs as playlist `b`. |
| `+` | Friend | `a + b` | Returns a new playlist containing the songs whose titles appear in **both** `a` and `b` (the common songs). |
| `-` | Friend | `a - b` | Returns a new playlist containing the songs in `a` whose titles do **not** appear in `b` (the unique songs). |
| `--` (postfix) | Member | `a--` | Removes the last song from the playlist. |
| `[]` | Member | `a[i]` | Plays the song at index `i`: prints its title and remaining duration, and returns the `Song`. |
| `<<` | Friend | `cout << a` | Prints the title of every song in the playlist, one per line. |

Songs are matched by **title only** when computing common and unique songs.

---

## Build and Run

### Requirements

- A C++ compiler with C++11 support or newer (for example `g++` or `clang++`)

### Compile

From the project folder:

```bash
g++ -std=c++11 main.cpp MusicTrack.cpp -o musictrack
```

### Run

On Linux or macOS:

```bash
./musictrack
```

On Windows:

```bash
musictrack.exe
```

You can also compile and run the project in any C++ IDE (Code::Blocks, Visual Studio, CLion, and so on) by adding all four files to one project.

---

## Usage Guide

When the program starts it shows this menu:

```
	SYSTEM MAIN MENU
	================
[01] Create a new playlist
[02] Add new songs to a playlist
[03] Remove a playlist
[04] Copy a playlist
[05] Display total playlists created
[06] Show the longest song among all playlists
[07] Compare two playlists
[08] Play a song by index
[09] Display common songs
[10] Display unique songs
[11] Remove last song
[12] Print all songs
[13] Exit
Pick an option:
```

**Important:** playlists and songs are referred to by their **1-based number** (the first playlist is `1`, the first song is `1`), in the order they were created or entered.

| Option | What it asks for | What happens |
|--------|------------------|--------------|
| **1** | Number of songs, then each title and duration | Creates a new playlist and makes it the **current playlist**. |
| **2** | Song title and duration | Adds a song to the current playlist (the most recently created one). |
| **3** | Playlist number | Deletes that playlist and removes it from the list. |
| **4** | Playlist number | Copies that playlist and appends the copy to the end of the list. |
| **5** | Nothing | Shows how many playlists exist. |
| **6** | Nothing | Shows the title and duration of the longest song entered across all playlists. |
| **7** | Two playlist numbers | Reports which playlist has greater than or equal size. |
| **8** | Playlist number and song number | Displays "Song playing" with the title and the minutes until it ends. |
| **9** | Two playlist numbers | Prints the songs both playlists share. |
| **10** | Two playlist numbers | Prints the songs in the first playlist that are missing from the second. |
| **11** | Playlist number | Removes the last song of that playlist. |
| **12** | Playlist number | Prints all song titles in that playlist. |
| **13** | Nothing | Exits the program. |

---

## Example Session

The following shows how two playlists can be created and compared.

```
Pick an option: 1
Enter number of songs: 3
Enter song #1 title: Song A
Enter song #1 duration in minutes: 3.5
Enter song #2 title: Song B
Enter song #2 duration in minutes: 4.2
Enter song #3 title: Song C
Enter song #3 duration in minutes: 2.8
Playlist created!

Pick an option: 1
Enter number of songs: 2
Enter song #1 title: Song B
Enter song #1 duration in minutes: 4.2
Enter song #2 title: Song D
Enter song #2 duration in minutes: 5.0
Playlist created!

Pick an option: 9
Enter first playlist number: 1
Enter second playlist number: 2
Common songs:
Song B

Pick an option: 10
Enter first playlist number: 1
Enter second playlist number: 2
Unique songs:
Song A
Song C

Pick an option: 6
Longest song: Song D
Duration: 5 minutes
```

---

## Known Limitations

This project was built as a learning exercise, so a few edge cases are not handled:

- **No input validation.** Playlist numbers, song numbers, and menu input are not range-checked, and non-numeric input is not handled.
- **Option 2 requires a current playlist.** It adds to the most recently created playlist, so a playlist must exist first, and it will not work as intended right after the current playlist has been removed.
- **No copy assignment operator.** The class defines a copy constructor and destructor but not `operator=`, so assigning one `MusicTrack` to another (which `std::vector` does when erasing elements) copies the pointer instead of the data.
- **Longest song is never recalculated.** It is only updated when songs are added, so removing a song or playlist does not lower it.
- **Removing the last song of an empty playlist** is not guarded against.
- **Duplicate titles** within a playlist can produce repeated entries in the results of `+`.

---

## Possible Improvements

- Add a copy assignment operator (completing the Rule of Three) and range checks on all indexes.
- Validate user input and recover cleanly from invalid entries.
- Let the user choose which playlist option 2 adds to.
- Recalculate the longest song when songs or playlists are removed.
- Replace the raw `Song*` array with `std::vector<Song>` to simplify memory management.
- Save and load playlists from a file.
- Add search and sort functions, for example by title or duration.

---

## Authors

- **Seif Hussein Mohamed Aboelazaim**
- **Omar Rashad Hassan Rashad**

Cairo University, Faculty of Computer Science and Artificial Intelligence (FCAI)
