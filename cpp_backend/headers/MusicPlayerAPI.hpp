#pragma once
#include <string>
#include <vector>
#include "Song.hpp"

// C++ DLL API for C# Frontend
namespace MusicPlayerAPI
{
    struct SongData
    {
        char title[256];
        char artist[256];
        int duration;
    };

    // Playlist Operations
    extern "C" 
    {
        // Initialize backend
        __declspec(dllexport) void InitBackend();

        // Playlist operations
        __declspec(dllexport) int GetPlaylistSize();
        __declspec(dllexport) int AddSongToPlaylist(const char* title, const char* artist, int duration);
        __declspec(dllexport) int RemoveSongFromPlaylist(int index);
        __declspec(dllexport) int GetPlaylistSong(int index, SongData* outSong);
        __declspec(dllexport) void ClearPlaylist();
        __declspec(dllexport) int GetAllSongs(SongData* outArray, int maxSize);

        // Player operations
        __declspec(dllexport) void PlaySong(int index);
        __declspec(dllexport) void PauseSong();
        __declspec(dllexport) void ResumeSong();
        __declspec(dllexport) void StopSong();
        __declspec(dllexport) int GetCurrentSongIndex();
        __declspec(dllexport) int GetPlaybackState(); // 0=STOPPED, 1=PLAYING, 2=PAUSED
        __declspec(dllexport) float GetProgress(); // 0.0 - 1.0

        // Last.fm API Search
        __declspec(dllexport) int SearchFromLastFM(const char* query, SongData* outArray, int maxResults);
        __declspec(dllexport) int GetTopTracks(SongData* outArray, int maxResults);

        // File operations
        __declspec(dllexport) int SavePlaylist(const char* filename);
        __declspec(dllexport) int LoadPlaylist(const char* filename);

        // Cleanup
        __declspec(dllexport) void ShutdownBackend();
    }
}
