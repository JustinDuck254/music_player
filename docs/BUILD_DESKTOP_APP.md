╔═══════════════════════════════════════════════════════════════╗
║      🎵 MUSIC PLAYER - Desktop App Build Guide 🎵            ║
║         C# WinForms + C++ Backend (DLL)                       ║
╚═══════════════════════════════════════════════════════════════╝

## 📋 REQUIREMENTS

1. **C++ Compiler**: MinGW-w64 (MSYS2 UCRT64) ✓ Already installed
2. **C# Compiler**: Visual Studio Community or .NET SDK ✓ Needed

---

## 🔧 STEP 1: BUILD C++ DLL

### 1.1 Create DLL Build Project

Visual Studio or MinGW:
```powershell
cd C:\Users\phulo\Documents\Code\Projects\music_player

# Set path
$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path

# Build DLL with all sources
g++ -Iheaders -std=c++17 -O2 -Wall -shared `
  src/Node.cpp src/Playlist.cpp src/Song.cpp `
  src/SystemManager.cpp src/APIManager.cpp src/FileManager.cpp `
  src/LastFMManager.cpp src/Player.cpp src/MusicPlayer.cpp `
  src/MusicPlayerAPI.cpp `
  -o MusicPlayerDLL.dll

# Verify DLL created
dir MusicPlayerDLL.dll
```

Expected output:
```
✅ MusicPlayerDLL.dll (500 KB - 1 MB)
```

---

## 🎨 STEP 2: BUILD C# FRONTEND

### 2.1 Option A: Using Visual Studio (Recommended)

1. Open Visual Studio Community
2. File → New → Project
3. Select "Windows Forms App (.NET Framework)" or ".NET"
4. Project name: "MusicPlayerUI"
5. Add the files:
   - MusicPlayerUI.cs (Main form)
   - MusicPlayerDLLWrapper.cs (P/Invoke wrapper)
6. Build → Build Solution (Ctrl+Shift+B)
7. Copy MusicPlayerDLL.dll to bin/Debug/

### 2.2 Option B: Using .NET CLI (if VS not installed)

```powershell
# Create new WinForms project
dotnet new winforms -n MusicPlayerUI

# Add the source files
Copy-Item MusicPlayerUI.cs -Destination MusicPlayerUI/
Copy-Item MusicPlayerDLLWrapper.cs -Destination MusicPlayerUI/

# Build
cd MusicPlayerUI
dotnet build

# Copy DLL to output
Copy-Item ..\MusicPlayerDLL.dll -Destination bin/Debug/net6.0-windows/
```

---

## 📂 STEP 3: DEPLOY

### 3.1 Project Structure

```
music_player/
├── MusicPlayerDLL.dll         ← C++ Backend
├── MusicPlayerUI.exe           ← C# Frontend
├── headers/
│   ├── Song.hpp
│   ├── Playlist.hpp
│   ├── Player.hpp
│   ├── MusicPlayerAPI.hpp
│   └── ...
├── src/
│   ├── Song.cpp
│   ├── Playlist.cpp
│   ├── Player.cpp
│   ├── MusicPlayerAPI.cpp
│   └── ...
├── MusicPlayerUI.cs            ← C# UI
├── MusicPlayerDLLWrapper.cs    ← P/Invoke Bridge
└── README.md
```

### 3.2 Run Application

**From Command Line:**
```powershell
.\MusicPlayerUI.exe
```

**From VS Code:**
```powershell
dotnet run
```

---

## 🔌 HOW IT WORKS

┌─────────────────────────────────────────────────────┐
│  C# WinForms Frontend (UI Thread)                  │
│  ┌────────────────────────────────────────────────┐ │
│  │  MusicPlayerForm (Main Window)                 │ │
│  │  ├─ Playlist View (ListBox)                    │ │
│  │  ├─ Play/Pause/Stop Buttons                    │ │
│  │  ├─ Search Box + Last.fm Integration           │ │
│  │  └─ Now Playing Display                        │ │
│  └──────────┬────────────────────────────────────┘ │
│             │ P/Invoke Calls                       │
│             │ MusicPlayerDLLWrapper.cs             │
│             ▼                                       │
└─────────────────────────────────────────────────────┘
           │
           │ DLL Import
           │
┌──────────▼────────────────────────────────────────┐
│  C++ DLL Backend (MusicPlayerAPI.cpp)            │
│  ┌────────────────────────────────────────────────┐ │
│  │  Global MusicPlayer Instance                  │ │
│  │  ├─ Playlist (Circular Linked List)           │ │
│  │  ├─ Player (Playback State)                   │ │
│  │  ├─ Last.fm API Calls                         │ │
│  │  └─ File Management                           │ │
│  └────────────────────────────────────────────────┘ │
│                                                     │
└──────────────────────────────────────────────────────┘

**Data Flow:**
1. User clicks "Play" in C# UI
2. C# calls MusicPlayerDLL.PlaySong(index)
3. C++ DLL accesses global Playlist
4. Player state updates in C++
5. Next update cycle, C# reads progress via GetProgress()
6. C# updates display

---

## 🧪 TESTING

### Test Checklist

After building:

□ DLL loads without errors
□ Playlist displays 5 demo songs
□ Play button works
□ Pause/Resume works
□ Stop button resets display
□ Search box accepts input
□ Progress updates in real-time
□ Now Playing display shows current song

### Debug P/Invoke Issues

**If DLL not found:**
```powershell
# Check if DLL exists
Test-Path MusicPlayerDLL.dll

# Check DLL dependencies
dumpbin /dependents MusicPlayerDLL.dll

# Required system DLLs should appear
```

**If function not found:**
```csharp
// In MusicPlayerDLLWrapper.cs, check:
// 1. Function name matches C++ exactly
// 2. CallingConvention = CallingConvention.Cdecl
// 3. DLL_NAME = "MusicPlayerDLL.dll"
// 4. DLL in same directory as .exe
```

---

## 📝 FEATURES INCLUDED

✅ Playlist Management
   • Add/Remove songs
   • View all songs
   • Double-click to play

✅ Playback Controls
   • Play/Pause/Stop
   • Progress display
   • Now Playing info

✅ Search Integration
   • Search via Last.fm API
   • Browse top tracks
   • Add songs to playlist

✅ File Management
   • Save playlist (JSON)
   • Load playlist
   • Persistent storage

✅ Visual UI
   • Dark theme (Spotify-like)
   • Status bar
   • Real-time updates

---

## 🚀 NEXT STEPS (Optional Enhancements)

1. **Real HTTP Requests**
   - Replace mock Last.fm with actual curl calls
   - Requires: libcurl library

2. **Audio Playback**
   - Integrate WinMM or SDL2
   - Actually play audio files

3. **More Features**
   - Volume control
   - Shuffle/Repeat modes
   - Equalizer
   - Themes

4. **Database**
   - SQLite for local caching
   - User preferences
   - Play history

---

## ❓ TROUBLESHOOTING

**Problem: "Unable to load DLL"**
→ Solution: DLL must be in same folder as .exe

**Problem: "Function not found in DLL"**
→ Solution: Check extern "C" in MusicPlayerAPI.hpp

**Problem: "Playlist not loading"**
→ Solution: Run InitBackend() first in form constructor

**Problem: "P/Invoke marshaling error"**
→ Solution: Check SongData struct layout matches both C++ and C#

---

## 📞 BUILD SUPPORT

Command to display debug info:
```powershell
# C++
g++ --version
# MinGW-w64 x86_64-w64-mingw32 (UCRT), built 2024

# C#
dotnet --version
# or Visual Studio version info
```

Last updated: November 9, 2025
Project: Spotify-like Music Player (Windows Desktop App)
