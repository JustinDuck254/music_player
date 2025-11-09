#include "MusicPlayerAPI.hpp"
#include "MusicPlayer.hpp"
#include "LastFMManager.hpp"
#include <cstring>
#include <vector>

// Global instances
static MusicPlayer* g_musicPlayer = nullptr;

namespace MusicPlayerAPI
{
    void InitBackend()
    {
        if (!g_musicPlayer)
        {
            g_musicPlayer = new MusicPlayer();
            // Initialize mock songs
            Song* song1 = new Song("Blinding Lights", "The Weeknd", 200);
            Song* song2 = new Song("Shape of You", "Ed Sheeran", 233);
            Song* song3 = new Song("Someone Like You", "Adele", 285);
            Song* song4 = new Song("Bad Guy", "Billie Eilish", 194);
            Song* song5 = new Song("Perfect", "Ed Sheeran", 263);
            
            g_musicPlayer->getPlaylist()->addLast(song1);
            g_musicPlayer->getPlaylist()->addLast(song2);
            g_musicPlayer->getPlaylist()->addLast(song3);
            g_musicPlayer->getPlaylist()->addLast(song4);
            g_musicPlayer->getPlaylist()->addLast(song5);
        }
    }

    int GetPlaylistSize()
    {
        if (!g_musicPlayer) InitBackend();
        return g_musicPlayer->getPlaylist()->getSize();
    }

    int AddSongToPlaylist(const char* title, const char* artist, int duration)
    {
        if (!g_musicPlayer) InitBackend();
        
        Song* newSong = new Song(title, artist, duration);
        g_musicPlayer->getPlaylist()->addLast(newSong);
        return GetPlaylistSize();
    }

    int RemoveSongFromPlaylist(int index)
    {
        if (!g_musicPlayer) InitBackend();
        
        g_musicPlayer->getPlaylist()->removeIndex(index);
        return GetPlaylistSize();
    }

    int GetPlaylistSong(int index, SongData* outSong)
    {
        if (!g_musicPlayer || !outSong) return -1;
        
        Song* song = g_musicPlayer->getPlaylist()->getAt(index);
        if (!song) return -1;
        
        strncpy_s(outSong->title, sizeof(outSong->title), song->getTitle().c_str(), _TRUNCATE);
        strncpy_s(outSong->artist, sizeof(outSong->artist), song->getArtist().c_str(), _TRUNCATE);
        outSong->duration = song->getDuration();
        
        return 0;
    }

    void ClearPlaylist()
    {
        if (!g_musicPlayer) InitBackend();
        g_musicPlayer->getPlaylist()->clear();
    }

    int GetAllSongs(SongData* outArray, int maxSize)
    {
        if (!g_musicPlayer || !outArray) return 0;
        
        int size = g_musicPlayer->getPlaylist()->getSize();
        int count = 0;
        
        for (int i = 0; i < size && count < maxSize; i++)
        {
            Song* song = g_musicPlayer->getPlaylist()->getAt(i);
            if (song)
            {
                strncpy_s(outArray[count].title, sizeof(outArray[count].title), 
                    song->getTitle().c_str(), _TRUNCATE);
                strncpy_s(outArray[count].artist, sizeof(outArray[count].artist), 
                    song->getArtist().c_str(), _TRUNCATE);
                outArray[count].duration = song->getDuration();
                count++;
            }
        }
        
        return count;
    }

    void PlaySong(int index)
    {
        if (!g_musicPlayer) InitBackend();
        
        Song* song = g_musicPlayer->getPlaylist()->getAt(index);
        if (song)
        {
            g_musicPlayer->getPlayer()->play(song);
        }
    }

    void PauseSong()
    {
        if (!g_musicPlayer) InitBackend();
        g_musicPlayer->getPlayer()->pause();
    }

    void ResumeSong()
    {
        if (!g_musicPlayer) InitBackend();
        g_musicPlayer->getPlayer()->resume();
    }

    void StopSong()
    {
        if (!g_musicPlayer) InitBackend();
        g_musicPlayer->getPlayer()->stop();
    }

    int GetCurrentSongIndex()
    {
        if (!g_musicPlayer) InitBackend();
        
        Song* current = g_musicPlayer->getPlayer()->getCurrentSong();
        if (!current) return -1;
        
        Playlist* playlist = g_musicPlayer->getPlaylist();
        for (int i = 0; i < playlist->getSize(); i++)
        {
            if (playlist->getAt(i) == current)
                return i;
        }
        return -1;
    }

    int GetPlaybackState()
    {
        if (!g_musicPlayer) InitBackend();
        return (int)g_musicPlayer->getPlayer()->getState();
    }

    float GetProgress()
    {
        if (!g_musicPlayer) InitBackend();
        return g_musicPlayer->getPlayer()->getProgress();
    }

    int SearchFromLastFM(const char* query, SongData* outArray, int maxResults)
    {
        if (!query || !outArray) return 0;
        
        LastFMManager::initialize("mock_api_key");
        std::vector<Song*> results = LastFMManager::searchTracks(query);
        
        int count = 0;
        for (const auto& song : results)
        {
            if (count >= maxResults) break;
            
            strncpy_s(outArray[count].title, sizeof(outArray[count].title), 
                song->getTitle().c_str(), _TRUNCATE);
            strncpy_s(outArray[count].artist, sizeof(outArray[count].artist), 
                song->getArtist().c_str(), _TRUNCATE);
            outArray[count].duration = song->getDuration();
            
            delete song; // Clean up temporary song objects
            count++;
        }
        
        return count;
    }

    int GetTopTracks(SongData* outArray, int maxResults)
    {
        if (!outArray) return 0;
        
        LastFMManager::initialize("mock_api_key");
        std::vector<Song*> results = LastFMManager::getTopTracks(maxResults);
        
        int count = 0;
        for (const auto& song : results)
        {
            if (count >= maxResults) break;
            
            strncpy_s(outArray[count].title, sizeof(outArray[count].title), 
                song->getTitle().c_str(), _TRUNCATE);
            strncpy_s(outArray[count].artist, sizeof(outArray[count].artist), 
                song->getArtist().c_str(), _TRUNCATE);
            outArray[count].duration = song->getDuration();
            
            delete song;
            count++;
        }
        
        return count;
    }

    int SavePlaylist(const char* filename)
    {
        if (!g_musicPlayer || !filename) return -1;
        return FileManager::savePlaylist(*g_musicPlayer->getPlaylist(), filename) ? 0 : -1;
    }

    int LoadPlaylist(const char* filename)
    {
        if (!g_musicPlayer || !filename) return -1;
        Playlist* loaded = FileManager::loadPlaylist(filename);
        if (loaded)
        {
            g_musicPlayer->getPlaylist()->clear();
            // Copy songs from loaded to current
            int size = loaded->getSize();
            for (int i = 0; i < size; i++)
            {
                Song* song = loaded->getAt(i);
                if (song)
                {
                    g_musicPlayer->getPlaylist()->addLast(
                        new Song(song->getTitle(), song->getArtist(), song->getDuration())
                    );
                }
            }
            delete loaded;
            return 0;
        }
        return -1;
    }

    void ShutdownBackend()
    {
        if (g_musicPlayer)
        {
            delete g_musicPlayer;
            g_musicPlayer = nullptr;
        }
    }
}
