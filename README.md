# music_player

Dự án C++ music player sử dụng circular doubly-linked list.

## Yêu cầu

- **MSYS2** với UCRT64 toolchain
- Cài đặt: `pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake`
- Thêm `C:\msys64\ucrt64\bin` vào PATH

## Build & Run (nhanh nhất)

Mở PowerShell trong thư mục project:

```powershell
# Đảm bảo ucrt64 trong PATH
$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path

# Compile tất cả file
g++ -Iheaders -std=c++17 -O2 -Wall src\Node.cpp src\Playlist.cpp src\Song.cpp src\main.cpp -o music_player.exe

# Chạy
.\music_player.exe
```

## Build với CMake (khuyến nghị cho dự án lớn)

```powershell
$env:Path = "C:\msys64\ucrt64\bin;" + $env:Path
mkdir -Force build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
.\music_player.exe
```

## Cấu trúc project

```
music_player/
├── headers/          # Header files (.hpp)
│   ├── Node.hpp
│   ├── Playlist.hpp
│   └── Song.hpp
├── src/             # Source files (.cpp)
│   ├── Node.cpp
│   ├── Playlist.cpp
│   ├── Song.cpp
│   └── main.cpp
├── CMakeLists.txt
└── README.md
```

## Ghi chú

- **Toolchain**: Dùng UCRT64 (không phải mingw64) để tránh conflict
- **Playlist**: Circular doubly-linked list với head/tail pointers
- **Memory**: Node owns Song* — tự động cleanup khi delete node
