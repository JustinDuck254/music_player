╔══════════════════════════════════════════════════════════════════╗# Music Player - Spotify-like Desktop Application

║              🎵 MUSIC PLAYER - Desktop Application 🎵            ║

║         C# WinForms Frontend + C++ Backend (Windows)             ║A feature-rich C++ music player application built with circular doubly-linked list data structure, featuring playlist management, API integration, file storage, and interactive UI.

╚══════════════════════════════════════════════════════════════════╝

## Quick Start

# Music Player - Complete Desktop Application

### Prerequisites

A **professional Spotify-like music player** for Windows with:- **MSYS2** with UCRT64 toolchain

- 🎨 Modern C# WinForms UI (dark theme)- Installation: `pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake`

- 🔧 C++ backend with circular doubly-linked list- Add `C:\msys64\ucrt64\bin` to your PATH

- 🔌 P/Invoke integration between C# and C++

- 🎵 Last.fm API integration for real music data### Build

- 💾 JSON-based playlist persistence

- ⚡ High-performance playback simulationOpen PowerShell in the project directory:



---```powershell

# Option 1: Direct g++ compilation (Quick)

## 🚀 Quick Start (5 minutes)$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path

g++ -Iheaders -std=c++17 -O2 -Wall src\*.cpp -o music_player.exe

### Prerequisites

- **Windows 7+** (64-bit)# Option 2: With CMake (Recommended for larger projects)

- **.NET 6.0 SDK** - https://dotnet.microsoft.com/download$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path

- **MinGW-w64 UCRT64** (for building from source)mkdir -Force build

cd build

### Build & Run (Automatic)cmake -G "MinGW Makefiles" ..

cmake --build .

```powershell```

cd C:\Users\phulo\Documents\Code\Projects\music_player

.\build.ps1 -Target both     # Build both layers### Run

.\build.ps1 -Target run      # Launch app

``````powershell

.\music_player.exe

### Build & Run (Manual)```



```powershell## Features

# Build C++ DLL

$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path### 🎵 Playlist Management (Options 1-9)

cd cpp_backend- **Add songs** to end, beginning, or specific position

g++ -Iheaders -std=c++17 -O2 -Wall -shared src\*.cpp -o ..\build\MusicPlayerDLL.dll- **Remove songs** from any position

- **View entire playlist** with song details

# Build C# UI- **Get song info** at specific index

cd ..\csharp_frontend- **Clear playlist** to start fresh

dotnet build -c Release

### 🔍 Discovery Mode (Options 10-12)

# Run- **Search songs** by title (case-insensitive)

dotnet run --project MusicPlayerUI.csproj- **Browse trending** songs database

```- **Get recommendations** by genre

- **API integration** (mock database with 10+ popular songs)

---- Easily add discovered songs to your playlist



## 📁 Project Structure### 💾 File Management (Options 13-15)

- **Save playlists** to JSON format

```- **Load saved playlists** from disk

music_player/- **View all saved playlists**

├── cpp_backend/                 ← C++ Backend (DLL)- Automatic directory creation: `%USERPROFILE%\Music\MusicPlayer\Playlists\`

│   ├── headers/                 ← 10 header files

│   └── src/                     ← 12 source files### ⚙️ System Features

├── csharp_frontend/             ← C# Frontend (WinForms)- **Input validation** for all user inputs

│   ├── MusicPlayerUI.cs         ← Main app (530 lines)- **Exception handling** for robust error management

│   ├── MusicPlayerDLLWrapper.cs ← P/Invoke bridge- **System logging** with timestamps

│   └── MusicPlayerUI.csproj     ← Project file- **Real-time feedback** with success/error/warning messages

├── docs/                        ← Documentation

│   ├── QUICKSTART_DESKTOP.md    ← START HERE ⭐## Menu Guide

│   ├── ARCHITECTURE.md

│   └── BUILD_DESKTOP_APP.md```

├── build/                       ← Build outputs========================================

│   ├── MusicPlayerDLL.dll         === MUSIC PLAYER ===

│   └── (compiled artifacts)========================================

├── build.ps1                    ← Master build script

└── README.md                    ← This file--- PLAYLIST MANAGEMENT ---

```[1] Add Song to End

[2] Add Song at Beginning

---[3] Add Song at Position

[4] View Playlist

## ✨ Features[5] Remove First Song

[6] Remove Last Song

### 🎨 User Interface[7] Remove Song at Position

✅ Dark theme (Spotify-style)[8] Get Song at Position

✅ Responsive layout[9] Clear Playlist

✅ Playlist ListBox

✅ Real-time updates--- DISCOVERY (API) ---

✅ Professional styling[10] Search Songs

[11] Browse Trending

### 🎵 Playback[12] Get Recommendations

✅ Play/Pause/Stop buttons

✅ Now Playing display--- FILE MANAGEMENT ---

✅ Progress tracking[13] Save Playlist

✅ Song information[14] Load Playlist

✅ Playback state[15] View Saved Playlists



### 🔍 Search[0] Exit

✅ Last.fm integration========================================

✅ Top tracks browsing```

✅ Recommendations

✅ Add to playlist## Usage Examples



### 📁 File Management### Example 1: Add and View Songs

✅ Save playlists (JSON)```

✅ Load playlists1. Choose [1] "Add Song to End"

✅ Persistent storage2. Enter: Title = "Blinding Lights"

          Artist = "The Weeknd"

---          Duration = 200

3. Repeat for more songs

## 🏗️ Architecture4. Choose [4] "View Playlist"

```

### Three-Layer System

### Example 2: Search and Discover

``````

Layer 1: C# WinForms UI1. Choose [10] "Search Songs"

    ↓ (P/Invoke)2. Enter search query: "Shape of You"

Layer 2: C++ DLL API (18 exported functions)3. Select song number to add (1, 2, 3...)

    ↓ (Object method calls)4. Song added to current playlist!

Layer 3: C++ Core Logic (1500+ lines)```

```

### Example 3: Save and Load

**Key Features:**```

- Seamless C# ↔ C++ communication1. Build your playlist

- Automatic struct marshaling2. Choose [13] "Save Playlist"

- Memory management3. Enter name: "My Favorites"

- Exception handling4. Later, choose [14] "Load Playlist"

5. Enter name: "My Favorites"

---6. Playlist restored!

```

## 📊 Statistics

## Project Structure

| Metric | Value |

|--------|-------|```

| **C++ Lines** | 1500+ |music_player/

| **C# Lines** | 670+ |├── headers/                    # C++ header files

| **Documentation** | 500+ |│   ├── Song.hpp               # Song data model

| **Total** | 2800+ |│   ├── Node.hpp               # Doubly-linked list node

| **Build Time** | 15 sec |│   ├── Playlist.hpp           # Circular doubly-linked list

| **Size** | 150 KB exe + 800 KB dll |│   ├── MusicPlayer.hpp        # Main application controller

│   ├── UI.hpp                 # User interface (menus/prompts)

---│   ├── SystemManager.hpp      # System utilities & logging

│   ├── APIManager.hpp         # API integration (search/trending)

## 🛠️ Build Commands│   └── FileManager.hpp        # File I/O operations

├── src/                       # C++ implementation files

```powershell│   ├── *.cpp                  # Corresponding implementations

.\build.ps1                 # Build both (default)│   └── main.cpp               # Entry point

.\build.ps1 -Target cpp     # Build C++ DLL only├── CMakeLists.txt             # CMake build configuration

.\build.ps1 -Target csharp  # Build C# UI only├── README.md                  # This file

.\build.ps1 -Target both    # Build both└── .gitignore                 # Git ignore rules

.\build.ps1 -Target run     # Run application```

.\build.ps1 -Target clean   # Clean artifacts

```## Architecture



---### Data Structure: Circular Doubly-Linked List

- **Node**: Wrapper around Song* pointer

## 📚 Documentation- **Playlist**: Circular list with head/tail pointers

- **Song**: Data model (title, artist, duration)

**Start with:** `docs/QUICKSTART_DESKTOP.md` ⭐- O(1) operations: Insert at ends, size query

- O(n) operations: Insert/remove at middle positions

| Document | Purpose |

|----------|---------|### Design Pattern: OOP + Manager Classes

| QUICKSTART_DESKTOP.md | 5-minute setup |- **MusicPlayer**: Main orchestrator

| ARCHITECTURE.md | Technical design |- **UIManager**: Console UI handling

| BUILD_DESKTOP_APP.md | Full guide |- **SystemManager**: System operations & logging

| README.md | Overview |- **APIManager**: Data fetching & search

- **FileManager**: Persistence layer

---

### Error Handling

## 🔧 Technology Stack- Try-catch blocks for all operations

- Input validation for user choices

- **Frontend:** C# WinForms (.NET 6.0)- Graceful exception handling

- **Backend:** C++ (C++17)- Detailed error/warning/success logging

- **Compiler:** MinGW-w64 g++ 14.2.0

- **Data Structure:** Circular doubly-linked list## Song Database (Mock API)

- **Integration:** P/Invoke

- **Persistence:** JSONCurrent 10 popular songs:

- **API:** Last.fm (mock)1. Blinding Lights - The Weeknd (200s)

2. Shape of You - Ed Sheeran (233s)

---3. Someone Like You - Adele (285s)

4. Bad Guy - Billie Eilish (194s)

## 🚀 Next Steps5. Perfect - Ed Sheeran (263s)

6. Uptown Funk - Bruno Mars (269s)

1. **Read:** `docs/QUICKSTART_DESKTOP.md`7. Levitating - Dua Lipa (203s)

2. **Build:** `.\build.ps1 -Target both`8. Anti-Hero - Taylor Swift (228s)

3. **Run:** `.\build.ps1 -Target run`9. Heat Waves - Glass Animals (239s)

4. **Explore:** All features in the app10. As It Was - Harry Styles (183s)



---## Logging Output Example



## 🎓 Learning Outcomes```

[2025-11-09 14:30:45] [SUCCESS] System initialized successfully!

This project demonstrates:[2025-11-09 14:30:50] [SUCCESS] Song 'Blinding Lights' added to the end of playlist!

- ✅ Circular doubly-linked list implementation[2025-11-09 14:31:00] [INFO] Searching songs: 'shape'

- ✅ OOP design in C++[2025-11-09 14:31:05] [SUCCESS] Found 1 songs!

- ✅ WinForms UI in C#[2025-11-09 14:31:10] [INFO] Playlist saved to: ...\Playlists\MyPlaylist.json

- ✅ P/Invoke platform interoperability```

- ✅ DLL creation and usage

- ✅ JSON file I/O## Technical Details

- ✅ Build automation

- ✅ Memory management### Build Information

- ✅ API integration- **Language**: C++17

- **Compiler**: g++ (MSYS2 UCRT64)

---- **Optimization**: -O2

- **Warning Level**: -Wall

**Ready to get started?**

### Files Generated

```powershell- `music_player.exe` - Main executable (~500KB)

.\build.ps1 -Target both- `Playlists/*.json` - Saved playlists

.\build.ps1 -Target run

```### Memory Management

- Automatic cleanup through destructors

For detailed instructions, see: `docs/QUICKSTART_DESKTOP.md`- Node owns Song* pointers

- Playlist destructor cleans all nodes

Last Updated: November 9, 2025- Exception-safe resource handling


## Troubleshooting

### Build Issues
- **Error**: `mingw64/bin not found`
  - Solution: Add `C:\msys64\ucrt64\bin` to PATH
  
- **Error**: `fatal error: iostream: No such file or directory`
  - Solution: Ensure UCRT64 toolchain is installed

### Runtime Issues
- **Cannot save playlists**
  - Check: `%USERPROFILE%\Music\MusicPlayer\Playlists\` directory exists
  - The application auto-creates it on first save

- **Songs not appearing in search**
  - Try partial title search (case-insensitive)
  - Use [11] Browse Trending to see all available songs

## Future Enhancements

- [ ] Audio playback integration (SDL2, PortAudio)
- [ ] Real API integration (Spotify API, LastFM)
- [ ] Playlist sharing (JSON export/import)
- [ ] Song ratings and favorites
- [ ] Shuffle and repeat modes
- [ ] Playback history tracking
- [ ] Unit tests (Catch2, GoogleTest)
- [ ] Web UI (REST API with Qt frontend)

## Notes

- Use UCRT64 toolchain (not mingw64) to avoid conflicts
- Playlists are stored as JSON (human-readable)
- All inputs are validated before processing
- Timestamps are added to all log messages
- Application is 100% English (no Vietnamese text)

## Build Command Reference

```powershell
# Quick build
$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path
g++ -Iheaders -std=c++17 -O2 -Wall src\*.cpp -o music_player.exe

# Run
.\music_player.exe

# Clean
Remove-Item *.exe, *.o -ErrorAction SilentlyContinue
```

## License

This project is open source and available under the MIT License.

## Author

Created as a demonstration of C++ OOP principles, data structures, and application development.

---

**Enjoy your Music Player! 🎵**
