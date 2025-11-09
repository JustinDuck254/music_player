#include "Player.hpp"
#include "SystemManager.hpp"
#include <iostream>
#include <iomanip>

Player::Player() 
    : currentSong(nullptr), state(STOPPED), elapsedSeconds(0), wasPaused(false), pausedTime(0) {
    // Constructor
}

Player::~Player() {
    // Don't delete currentSong as it's managed by Playlist
}

void Player::play(Song* song) {
    if (song == nullptr) {
        SystemManager::logWarning("Cannot play null song!");
        return;
    }
    
    currentSong = song;
    state = PLAYING;
    elapsedSeconds = 0;
    startTime = std::chrono::steady_clock::now();
    wasPaused = false;
    
    SystemManager::logSuccess("▶️  Now playing: " + song->getTitle() + " - " + song->getArtist());
}

void Player::pause() {
    if (state == PLAYING) {
        state = PAUSED;
        pausedTime = elapsedSeconds;
        wasPaused = true;
        SystemManager::logInfo("⏸️  Paused: " + currentSong->getTitle());
    }
}

void Player::resume() {
    if (state == PAUSED) {
        state = PLAYING;
        startTime = std::chrono::steady_clock::now();
        SystemManager::logInfo("▶️  Resumed: " + currentSong->getTitle());
    }
}

void Player::stop() {
    state = STOPPED;
    currentSong = nullptr;
    elapsedSeconds = 0;
    SystemManager::logInfo("⏹️  Stopped playback");
}

Player::PlaybackState Player::getState() const {
    return state;
}

Song* Player::getCurrentSong() const {
    return currentSong;
}

int Player::getElapsedTime() const {
    if (state == STOPPED) return 0;
    if (state == PAUSED) return pausedTime;
    
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime);
    return pausedTime + static_cast<int>(elapsed.count());
}

int Player::getRemainingTime() const {
    if (currentSong == nullptr) return 0;
    int total = currentSong->getDuration();
    return total - getElapsedTime();
}

void Player::setProgress(int percentage) {
    if (currentSong != nullptr && percentage >= 0 && percentage <= 100) {
        elapsedSeconds = (currentSong->getDuration() * percentage) / 100;
        pausedTime = elapsedSeconds;
    }
}

int Player::getProgress() const {
    if (currentSong == nullptr || currentSong->getDuration() == 0) return 0;
    int total = currentSong->getDuration();
    int elapsed = getElapsedTime();
    
    if (elapsed >= total) return 100;
    return (elapsed * 100) / total;
}

bool Player::isPlaying() const {
    return state == PLAYING;
}

std::string Player::formatTime(int seconds) const {
    int minutes = seconds / 60;
    int secs = seconds % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << secs;
    
    return oss.str();
}

std::string Player::getFormattedCurrentTime() const {
    return formatTime(getElapsedTime());
}

std::string Player::getFormattedTotalTime() const {
    if (currentSong == nullptr) return "00:00";
    return formatTime(currentSong->getDuration());
}

void Player::displayNowPlaying() const {
    if (state == STOPPED) {
        std::cout << "\n[STOPPED] No song playing\n";
        return;
    }
    
    if (currentSong == nullptr) return;
    
    std::cout << "\n========================================\n";
    std::cout << "       NOW PLAYING\n";
    std::cout << "========================================\n";
    std::cout << "🎵 " << currentSong->getTitle() << "\n";
    std::cout << "👤 " << currentSong->getArtist() << "\n";
    std::cout << "⏱️  " << getFormattedCurrentTime() << " / " << getFormattedTotalTime() << "\n";
    
    // Progress bar
    int progress = getProgress();
    std::cout << "📊 ";
    int barLength = 30;
    int filledLength = (progress * barLength) / 100;
    
    for (int i = 0; i < barLength; i++) {
        if (i < filledLength) std::cout << "█";
        else std::cout << "░";
    }
    std::cout << " " << progress << "%\n";
    
    // Status
    if (state == PLAYING) {
        std::cout << "Status: ▶️  PLAYING\n";
    } else if (state == PAUSED) {
        std::cout << "Status: ⏸️  PAUSED\n";
    }
    
    std::cout << "========================================\n";
}
