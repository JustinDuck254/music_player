#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include "Playlist.hpp"
#include "SystemManager.hpp"
#include "APIManager.hpp"
#include "FileManager.hpp"
#include "LastFMManager.hpp"
#include "Player.hpp"

/**
 * MusicPlayer class - Manages the music player application
 * Handles playlist operations, API integration, and file management
 */
class MusicPlayer {
private:
    Playlist playlist;
    bool running;
    Player player;

public:
    /**
     * Constructor - Initialize the music player
     */
    MusicPlayer();

    /**
     * Destructor - Clean up resources
     */
    ~MusicPlayer();

    /**
     * Run the music player with interactive menu
     */
    void run();

private:
    /**
     * Handle user menu choice
     */
    void handleMenuChoice(int choice);

    /**
     * Add song to end of playlist
     */
    void addSongToEnd();

    /**
     * Add song to beginning of playlist
     */
    void addSongToBeginning();

    /**
     * Add song at specific position
     */
    void addSongAtPosition();

    /**
     * View entire playlist
     */
    void viewPlaylist();

    /**
     * Remove first song
     */
    void removeFirstSong();

    /**
     * Remove last song
     */
    void removeLastSong();

    /**
     * Remove song at specific position
     */
    void removeSongAtPosition();

    /**
     * Get and display song at position
     */
    void getSongAtPosition();

    /**
     * Clear entire playlist
     */
    void clearAllSongs();

    /**
     * Search songs from API
     */
    void searchSongsFromAPI();

    /**
     * Browse trending songs
     */
    void browseTrendingSongs();

    /**
     * Browse recommendations
     */
    void browseRecommendations();

    /**
     * Save playlist to file
     */
    void savePlaylist();

    /**
     * Load playlist from file
     */
    void loadPlaylist();

    /**
     * Show saved playlists
     */
    void viewSavedPlaylists();

    /**
     * Display welcome message
     */
    void displayWelcome();

    /**
     * Display main menu with all options
     */
    void displayEnhancedMenu();

    /**
     * Play song from playlist
     */
    void playSong();

    /**
     * Show now playing info
     */
    void showNowPlaying();

    /**
     * Pause/Resume playback
     */
    void togglePlayback();

    /**
     * Search from Last.fm API (real music data)
     */
    void searchFromLastFM();

    /**
     * Browse Last.fm top tracks
     */
    void browseLastFMTop();

public:
    /**
     * Getter for playlist (used by DLL wrapper)
     */
    Playlist* getPlaylist() { return &playlist; }

    /**
     * Getter for player (used by DLL wrapper)
     */
    Player* getPlayer() { return &player; }
};

#endif // MUSICPLAYER_HPP
