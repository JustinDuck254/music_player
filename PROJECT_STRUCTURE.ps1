#!/usr/bin/env pwsh
# ============================================================================
# PROJECT STRUCTURE - Visual Overview
# ============================================================================
# This file provides a complete visual overview of the project organization

$structure = @"
╔══════════════════════════════════════════════════════════════════════════╗
║                    🎵 MUSIC PLAYER - PROJECT STRUCTURE 🎵              ║
╚══════════════════════════════════════════════════════════════════════════╝

music_player/                          [Project Root]
│
├── 📁 cpp_backend/                    [C++ Backend (DLL Library)]
│   │
│   ├── 📁 headers/                    [C++ Header Files - 10 files]
│   │   ├── Song.hpp                   [Data model for music tracks]
│   │   ├── Node.hpp                   [Linked list node container]
│   │   ├── Playlist.hpp               [Circular doubly-linked list]
│   │   ├── Player.hpp                 [Playback state machine]
│   │   ├── MusicPlayer.hpp            [Application controller]
│   │   ├── MusicPlayerAPI.hpp         [DLL export interface] ⭐
│   │   ├── LastFMManager.hpp          [Last.fm API integration]
│   │   ├── FileManager.hpp            [JSON persistence]
│   │   ├── APIManager.hpp             [Mock music database]
│   │   ├── SystemManager.hpp          [Logging & validation]
│   │   └── UI.hpp                     [Console UI utilities]
│   │
│   └── 📁 src/                        [C++ Implementation - 12 files]
│       ├── Song.cpp                   [Song class implementation]
│       ├── Node.cpp                   [Node class implementation]
│       ├── Playlist.cpp               [Circular list implementation]
│       ├── Player.cpp                 [Playback controller]
│       ├── MusicPlayer.cpp            [App controller]
│       ├── MusicPlayerAPI.cpp         [DLL wrapper functions] ⭐
│       ├── LastFMManager.cpp          [API integration]
│       ├── FileManager.cpp            [File I/O]
│       ├── APIManager.cpp             [Database operations]
│       ├── SystemManager.cpp          [System utilities]
│       ├── UI.cpp                     [Console UI]
│       └── main.cpp                   [Console app entry point]
│
├── 📁 csharp_frontend/                [C# Frontend (WinForms UI)]
│   │
│   ├── MusicPlayerUI.cs               [Main WinForms application] ⭐
│   │                                  [530 lines - UI & logic]
│   │
│   ├── MusicPlayerDLLWrapper.cs       [P/Invoke bridge layer] ⭐
│   │                                  [140 lines - DLL import wrapper]
│   │
│   ├── MusicPlayerUI.csproj           [C# Project file]
│   │                                  [.NET 6.0 configuration]
│   │
│   ├── 📁 bin/
│   │   └── 📁 Release/
│   │       └── 📁 net6.0-windows/     [Compiled output]
│   │           ├── MusicPlayerUI.exe  [Main executable]
│   │           ├── MusicPlayerUI.dll  [C# assembly]
│   │           └── MusicPlayerDLL.dll [C++ backend (copied)]
│   │
│   └── 📁 obj/                        [Build artifacts]
│
├── 📁 docs/                           [Documentation]
│   │
│   ├── QUICKSTART_DESKTOP.md          [Quick start guide] ⭐ START HERE
│   │                                  [250+ lines - 5 min setup]
│   │
│   ├── ARCHITECTURE.md                [Technical architecture]
│   │                                  [200+ lines - system design]
│   │
│   └── BUILD_DESKTOP_APP.md           [Full build guide]
│                                      [200+ lines - detailed instructions]
│
├── 📁 build/                          [Build Artifacts & Outputs]
│   ├── MusicPlayerDLL.dll             [Compiled C++ backend] (~800 KB)
│   └── (other build artifacts)
│
├── 📄 build.ps1                       [Master Build Script] ⭐
│                                      [PowerShell build automation]
│
├── 📄 README.md                       [Project Overview]
│                                      [This is the main documentation]
│
└── 📄 .vscode/
    ├── tasks.json                     [VS Code build tasks]
    └── launch.json                    [VS Code debug config]


╔══════════════════════════════════════════════════════════════════════════╗
║                            KEY FILES EXPLAINED                           ║
╚══════════════════════════════════════════════════════════════════════════╝

📌 C++ BACKEND LAYER
═══════════════════════════════════════════════════════════════════════════

🔹 MusicPlayerAPI.hpp/cpp [DLL Interface]
   Purpose: Exports C++ functions for C# to call
   Functions: 18 exported extern "C" functions
   Example: InitBackend(), PlaySong(index), GetPlaylistSize()

🔹 Core Classes (Headers + Implementation)
   Song.hpp/cpp          → Data model (title, artist, duration)
   Node.hpp/cpp          → Linked list node container
   Playlist.hpp/cpp      → Circular doubly-linked list manager
   Player.hpp/cpp        → Playback state machine
   MusicPlayer.hpp/cpp   → Main application controller

🔹 Support Classes
   LastFMManager         → Last.fm API integration (real music data)
   FileManager           → JSON save/load operations
   APIManager            → Mock music database (10 songs)
   SystemManager         → Logging, validation, error handling
   UI.hpp/cpp            → Console UI utilities


📌 C# FRONTEND LAYER
═══════════════════════════════════════════════════════════════════════════

🔹 MusicPlayerUI.cs [Main Application - 530 lines]
   └─ MusicPlayerForm class (WinForms Form)
      ├─ UI Components
      │  ├─ Header panel (title)
      │  ├─ Now Playing display
      │  ├─ Control buttons (Play/Pause/Stop)
      │  ├─ Playlist ListBox
      │  ├─ Search panel
      │  └─ Status bar
      │
      ├─ Event Handlers
      │  ├─ PlayButton_Click
      │  ├─ PauseButton_Click
      │  ├─ StopButton_Click
      │  ├─ SearchButton_Click
      │  └─ PlaylistView_DoubleClick
      │
      └─ Update Timer
         └─ Real-time progress updates (1 sec interval)

🔹 MusicPlayerDLLWrapper.cs [P/Invoke Bridge - 140 lines]
   ├─ MusicPlayerDLL class (P/Invoke declarations)
   │  └─ 18 [DllImport] function declarations
   │
   ├─ SongData struct (marshaling configuration)
   │  ├─ title (256-char string)
   │  ├─ artist (256-char string)
   │  └─ duration (int)
   │
   └─ MusicPlayerBackend helper class
      └─ Static wrapper methods for type conversions


📌 CONFIGURATION FILES
═══════════════════════════════════════════════════════════════════════════

🔹 build.ps1 [Master Build Script]
   Commands:
   .\build.ps1 -Target cpp      → Build C++ DLL only
   .\build.ps1 -Target csharp   → Build C# UI only
   .\build.ps1 -Target both     → Build both (default)
   .\build.ps1 -Target run      → Run application
   .\build.ps1 -Target clean    → Clean artifacts

🔹 MusicPlayerUI.csproj [C# Project Configuration]
   ├─ Target Framework: .NET 6.0 Windows
   ├─ Assembly Name: MusicPlayerUI
   ├─ Output Type: WinExe
   └─ Post-build: Copy MusicPlayerDLL.dll

🔹 .vscode/tasks.json [VS Code Build Tasks]
   ├─ Build C++ DLL (for C# Frontend)
   ├─ Build C# UI (WinForms)
   ├─ Build Complete App (C++ DLL + C# UI)
   ├─ Run C# Music Player UI
   └─ Clean Build Artifacts


╔══════════════════════════════════════════════════════════════════════════╗
║                            DATA FLOW OVERVIEW                            ║
╚══════════════════════════════════════════════════════════════════════════╝

COMPILATION FLOW
════════════════════════════════════════════════════════════════════════════

1. C++ Source Files (12 .cpp files)
   │
   ├─→ g++ compiler with -shared flag
   │
   └─→ MusicPlayerDLL.dll (800 KB)

2. C# Source Files (3 .cs files)
   │
   ├─→ dotnet build with .NET 6.0
   │
   └─→ MusicPlayerUI.exe (150 KB)


RUNTIME DATA FLOW
════════════════════════════════════════════════════════════════════════════

User Action (Button Click, Text Input, etc.)
      │
      ↓
C# Event Handler (MusicPlayerForm.cs)
      │
      ↓
P/Invoke Call (MusicPlayerDLLWrapper.cs)
      │
      ├─→ [DllImport("MusicPlayerDLL.dll")]
      │
      ↓
C++ DLL Function (MusicPlayerAPI.cpp)
      │
      ├─→ extern "C" __declspec(dllexport)
      │
      ↓
C++ Object Call (MusicPlayer, Playlist, Player, etc.)
      │
      ↓
Return Result to C#
      │
      ├─→ SongData struct
      ├─→ int (size, index, state)
      ├─→ float (progress)
      │
      ↓
Update UI Elements
      │
      ├─→ ListBox items
      ├─→ Label text
      ├─→ Button colors
      └─→ Status bar


╔══════════════════════════════════════════════════════════════════════════╗
║                        FILE ORGANIZATION LOGIC                           ║
╚══════════════════════════════════════════════════════════════════════════╝

WHY THIS STRUCTURE?

✅ cpp_backend/          [Separation of Concerns]
   - All C++ code isolated
   - Easy to rebuild DLL independently
   - Clear interface: MusicPlayerAPI.hpp
   - Supports future upgrades (real HTTP, audio playback)

✅ csharp_frontend/      [UI-specific code]
   - All C# UI code together
   - Can be replaced with WPF, Winui, etc.
   - Wrapper handles DLL marshaling
   - Easy to debug UI issues

✅ docs/                 [Documentation grouped]
   - Separate from code
   - Easier to maintain
   - Can be versioned independently
   - Better for project documentation

✅ build/                [Clean build artifacts]
   - Keeps root directory clean
   - Easy to clean all outputs
   - DLL and EXE in one place
   - Can be .gitignore'd

✅ build.ps1             [Single entry point]
   - One command builds everything
   - No need to remember complex commands
   - Handles all platforms/configurations
   - Easy automation


╔══════════════════════════════════════════════════════════════════════════╗
║                        QUICK COMMAND REFERENCE                           ║
╚══════════════════════════════════════════════════════════════════════════╝

# Navigate to project
cd C:\Users\phulo\Documents\Code\Projects\music_player

# Build everything
.\build.ps1

# Build just C++ backend
cd cpp_backend
g++ -Iheaders -std=c++17 -O2 -Wall -shared src\*.cpp -o ..\build\MusicPlayerDLL.dll

# Build just C# frontend
cd csharp_frontend
dotnet build -c Release

# Run the app
dotnet run --project csharp_frontend/MusicPlayerUI.csproj

# Clean all artifacts
.\build.ps1 -Target clean

# View file structure
tree /F /A

# List all C++ files
Get-ChildItem -Path cpp_backend -Recurse -Include *.hpp, *.cpp

# List all C# files
Get-ChildItem -Path csharp_frontend -Recurse -Include *.cs, *.csproj


╔══════════════════════════════════════════════════════════════════════════╗
║                            FILE SIZE SUMMARY                             ║
╚══════════════════════════════════════════════════════════════════════════╝

C++ Source Files:
  ├─ Headers:         ~300 KB total
  ├─ Implementation:  ~1500 KB total
  └─ Compiled DLL:    ~800 KB

C# Source Files:
  ├─ Source Code:     ~30 KB total
  └─ Compiled EXE:    ~150 KB

Documentation:
  └─ All docs:        ~50 KB total

Total Project (source): ~2 MB
Total Project (built):  ~1 MB


For more information, see:
  • README.md (overview)
  • docs/QUICKSTART_DESKTOP.md (quick start)
  • docs/ARCHITECTURE.md (technical details)

Last Updated: November 9, 2025
"@

Write-Host $structure
