# music_player (minimal scaffold)

This repository contains a minimal C++ project scaffold for a music player.

Build & run (quick g++ compile)

Open PowerShell in the project root and run:

```powershell
mkdir -Force build
g++ -Iheaders -std=c++17 -O2 -Wall src\main.cpp -o build\music_player.exe
.\build\music_player.exe
```

Using CMake (recommended for expansion)

```powershell
mkdir -Force build
cd build
cmake -G "MinGW Makefiles" ..   # if using MinGW/g++
cmake --build . --config Release
# then run the produced executable (path depends on generator)
# .\music_player.exe or .\Release\music_player.exe
```

Notes
- Ensure `g++` (MinGW-w64 or MSYS2) is installed and available in PATH on Windows.
- Use CMake to add libraries (SDL2/PortAudio/etc.) later.
