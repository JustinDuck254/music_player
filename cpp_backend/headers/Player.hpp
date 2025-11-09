#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Song.hpp"
#include <string>
#include <chrono>

/**
 * Player - Manages playback state and now-playing info
 * Tracks current song, play status, elapsed time, etc.
 */
class Player {
public:
    enum PlaybackState {
        STOPPED,
        PLAYING,
        PAUSED
    };

    /**
     * Constructor
     */
    Player();

    /**
     * Destructor
     */
    ~Player();

    /**
     * Start playing a song
     */
    void play(Song* song);

    /**
     * Pause current playback
     */
    void pause();

    /**
     * Resume from pause
     */
    void resume();

    /**
     * Stop playback
     */
    void stop();

    /**
     * Get current playback state
     */
    PlaybackState getState() const;

    /**
     * Get currently playing song
     */
    Song* getCurrentSong() const;

    /**
     * Get elapsed time in seconds
     */
    int getElapsedTime() const;

    /**
     * Get remaining time in seconds
     */
    int getRemainingTime() const;

    /**
     * Set playback progress (0-100)
     */
    void setProgress(int percentage);

    /**
     * Get playback progress (0-100)
     */
    int getProgress() const;

    /**
     * Check if currently playing
     */
    bool isPlaying() const;

    /**
     * Get formatted current time MM:SS
     */
    std::string getFormattedCurrentTime() const;

    /**
     * Get formatted total time MM:SS
     */
    std::string getFormattedTotalTime() const;

    /**
     * Display now playing info
     */
    void displayNowPlaying() const;

private:
    Song* currentSong;
    PlaybackState state;
    int elapsedSeconds;
    std::chrono::steady_clock::time_point startTime;
    bool wasPaused;
    int pausedTime;

    /**
     * Format seconds to MM:SS
     */
    std::string formatTime(int seconds) const;
};

#endif // PLAYER_HPP
