#include "MusicPlayer.hpp"
#include "UI.hpp"
#include "SystemManager.hpp"
#include <iostream>

MusicPlayer::MusicPlayer() : running(true) {
    // Constructor: Initialize with empty playlist
}

MusicPlayer::~MusicPlayer() {
    // Destructor: Cleanup happens automatically through Playlist destructor
}

void MusicPlayer::run() {
    try {
        SystemManager::initialize();
        
        // Initialize Last.fm API (using demo key - get your own at last.fm/api)
        LastFMManager::initialize("demo_api_key_for_testing");
        SystemManager::logInfo("Last.fm API integration enabled!");
        
        displayWelcome();
        
        while (running) {
            displayEnhancedMenu();
            int choice = UI::getUserChoice();
            handleMenuChoice(choice);
        }
        
        UI::clearScreen();
        std::cout << "\nThank you for using Music Player! Goodbye!\n\n";
        SystemManager::shutdown();
    } catch (const SystemException& e) {
        SystemManager::handleException(e);
        UI::displayError("A system error occurred!");
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        UI::displayError("An unexpected error occurred!");
    } catch (...) {
        UI::displayError("An unknown error occurred!");
    }
}

void MusicPlayer::displayWelcome() {
    UI::clearScreen();
    UI::displayHeader();
    std::cout << "\nWelcome to Music Player!\n";
    std::cout << "Manage your playlist easily with API integration.\n";
    std::cout << "Search, browse, and save your favorite songs!\n";
    UI::displaySeparator();
    std::cout << "\nPress Enter to continue...";
    std::cout.flush();
    
    // Safe input handling
    std::string dummy;
    if (std::getline(std::cin, dummy) && !dummy.empty()) {
        // Line read successfully
    }
    
    UI::clearScreen();
}

void MusicPlayer::handleMenuChoice(int choice) {
    switch (choice) {
        case 1:
            addSongToEnd();
            break;
        case 2:
            addSongToBeginning();
            break;
        case 3:
            addSongAtPosition();
            break;
        case 4:
            viewPlaylist();
            break;
        case 5:
            removeFirstSong();
            break;
        case 6:
            removeLastSong();
            break;
        case 7:
            removeSongAtPosition();
            break;
        case 8:
            getSongAtPosition();
            break;
        case 9:
            clearAllSongs();
            break;
        case 10:
            searchSongsFromAPI();
            break;
        case 11:
            browseTrendingSongs();
            break;
        case 12:
            browseRecommendations();
            break;
        case 13:
            savePlaylist();
            break;
        case 14:
            loadPlaylist();
            break;
        case 15:
            viewSavedPlaylists();
            break;
        case 16:
            searchFromLastFM();
            break;
        case 17:
            browseLastFMTop();
            break;
        case 18:
            playSong();
            break;
        case 19:
            showNowPlaying();
            break;
        case 0:
            running = false;
            break;
        default:
            UI::displayError("Invalid choice! Please try again.");
            break;
    }
    
    if (running && choice != 4 && choice != 11 && choice != 15 && choice != 19) {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        UI::clearScreen();
    }
}

void MusicPlayer::addSongToEnd() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::string title = SystemManager::getSafeString("Enter song title: ");
        std::string artist = SystemManager::getSafeString("Enter artist name: ");
        
        std::cout << "Enter duration (seconds): ";
        int duration = SystemManager::getSafeInteger(1, 3600);
        
        playlist.addLast(new Song(title, artist, duration));
        SystemManager::logSuccess("Song '" + title + "' added to the end of playlist!");
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        UI::displayError("Failed to add song!");
    }
}

void MusicPlayer::addSongToBeginning() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::string title = SystemManager::getSafeString("Enter song title: ");
        std::string artist = SystemManager::getSafeString("Enter artist name: ");
        
        std::cout << "Enter duration (seconds): ";
        int duration = SystemManager::getSafeInteger(1, 3600);
        
        playlist.addFirst(new Song(title, artist, duration));
        SystemManager::logSuccess("Song '" + title + "' added to the beginning of playlist!");
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        UI::displayError("Failed to add song!");
    }
}

void MusicPlayer::addSongAtPosition() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::string title = SystemManager::getSafeString("Enter song title: ");
        std::string artist = SystemManager::getSafeString("Enter artist name: ");
        
        std::cout << "Enter duration (seconds): ";
        int duration = SystemManager::getSafeInteger(1, 3600);
        
        std::cout << "Enter position (0-based): ";
        int index = SystemManager::getSafeInteger(0, playlist.getSize());
        
        playlist.addIndex(new Song(title, artist, duration), index);
        SystemManager::logSuccess("Song '" + title + "' added at position " + std::to_string(index) + "!");
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        UI::displayError("Failed to add song!");
    }
}

void MusicPlayer::viewPlaylist() {
    UI::clearScreen();
    UI::displayHeader();
    
    if (playlist.isEmpty()) {
        UI::displayMessage("Playlist is empty!");
    } else {
        UI::displayMessage("Current Playlist:");
        UI::displaySeparator();
        playlist.print();
        UI::displaySeparator();
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}

void MusicPlayer::removeFirstSong() {
    UI::clearScreen();
    UI::displayHeader();
    
    if (playlist.removeFirst()) {
        UI::displaySuccess("First song removed!");
    } else {
        UI::displayError("Playlist is empty!");
    }
}

void MusicPlayer::removeLastSong() {
    UI::clearScreen();
    UI::displayHeader();
    
    if (playlist.removeLast()) {
        UI::displaySuccess("Last song removed!");
    } else {
        UI::displayError("Playlist is empty!");
    }
}

void MusicPlayer::removeSongAtPosition() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::cout << "Enter position (0-based): ";
        int index = SystemManager::getSafeInteger(0, playlist.getSize() - 1);
        
        if (playlist.removeIndex(index)) {
            SystemManager::logSuccess("Song at position " + std::to_string(index) + " removed!");
        } else {
            SystemManager::logWarning("Failed to remove song at position " + std::to_string(index) + "!");
            UI::displayError("Invalid position or playlist is empty!");
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        UI::displayError("Failed to remove song!");
    }
}

void MusicPlayer::getSongAtPosition() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::cout << "Enter position (0-based): ";
        int index = SystemManager::getSafeInteger(0, playlist.getSize() - 1);
        
        Song* song = playlist.getAt(index);
        
        if (song) {
            UI::displayMessage("Song at position " + std::to_string(index) + ":");
            UI::displaySeparator();
            std::cout << song->toString() << "\n";
            UI::displaySeparator();
            SystemManager::logInfo("Retrieved song at position " + std::to_string(index) + "!");
        } else {
            SystemManager::logWarning("No song found at position " + std::to_string(index) + "!");
            UI::displayError("No song found at position " + std::to_string(index) + "!");
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        UI::displayError("Failed to retrieve song!");
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}

void MusicPlayer::clearAllSongs() {
    UI::clearScreen();
    UI::displayHeader();
    
    if (!playlist.isEmpty()) {
        playlist.clear();
        UI::displaySuccess("All songs have been removed!");
    } else {
        UI::displayMessage("Playlist is already empty!");
    }
}

void MusicPlayer::displayEnhancedMenu() {
    UI::displayHeader();
    std::cout << "\n--- PLAYLIST MANAGEMENT ---\n";
    std::cout << "[1] Add Song to End\n";
    std::cout << "[2] Add Song at Beginning\n";
    std::cout << "[3] Add Song at Position\n";
    std::cout << "[4] View Playlist\n";
    std::cout << "[5] Remove First Song\n";
    std::cout << "[6] Remove Last Song\n";
    std::cout << "[7] Remove Song at Position\n";
    std::cout << "[8] Get Song at Position\n";
    std::cout << "[9] Clear Playlist\n";
    std::cout << "\n--- DISCOVERY (API) ---\n";
    std::cout << "[10] Search Songs\n";
    std::cout << "[11] Browse Trending\n";
    std::cout << "[12] Get Recommendations\n";
    std::cout << "\n--- LAST.FM (REAL MUSIC DATA) ---\n";
    std::cout << "[16] Search Last.fm\n";
    std::cout << "[17] Browse Top Tracks\n";
    std::cout << "\n--- PLAYBACK ---\n";
    std::cout << "[18] Play Song from Playlist\n";
    std::cout << "[19] Show Now Playing\n";
    std::cout << "\n--- FILE MANAGEMENT ---\n";
    std::cout << "[13] Save Playlist\n";
    std::cout << "[14] Load Playlist\n";
    std::cout << "[15] View Saved Playlists\n";
    std::cout << "\n[0] Exit\n";
    UI::displaySeparator();
}

void MusicPlayer::searchSongsFromAPI() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::string query = SystemManager::getSafeString("Enter song title to search: ");
        auto results = APIManager::searchSongs(query);
        
        if (results.empty()) {
            UI::displayError("No songs found!");
            return;
        }
        
        UI::displayMessage("Search Results:");
        UI::displaySeparator();
        
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << (i + 1) << ". " << results[i]->toString() << "\n";
        }
        
        UI::displaySeparator();
        std::cout << "\nEnter song number to add (0 to skip): ";
        int choice = SystemManager::getSafeInteger(0, results.size());
        
        if (choice > 0 && choice <= (int)results.size()) {
            Song* selected = results[choice - 1];
            playlist.addLast(new Song(selected->getTitle(), selected->getArtist(), selected->getDuration()));
            UI::displaySuccess("Song added to playlist!");
        }
        
        for (auto s : results) {
            delete s;
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}

void MusicPlayer::browseTrendingSongs() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        auto trending = APIManager::getTrendingSongs();
        
        if (trending.empty()) {
            UI::displayError("No trending songs available!");
            return;
        }
        
        UI::displayMessage("Trending Songs:");
        UI::displaySeparator();
        
        for (size_t i = 0; i < trending.size(); ++i) {
            std::cout << (i + 1) << ". " << trending[i]->toString() << "\n";
        }
        
        UI::displaySeparator();
        std::cout << "\nEnter song number to add (0 to skip): ";
        int choice = SystemManager::getSafeInteger(0, trending.size());
        
        if (choice > 0 && choice <= (int)trending.size()) {
            Song* selected = trending[choice - 1];
            playlist.addLast(new Song(selected->getTitle(), selected->getArtist(), selected->getDuration()));
            UI::displaySuccess("Song added to playlist!");
        }
        
        for (auto s : trending) {
            delete s;
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}

void MusicPlayer::browseRecommendations() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::string genre = SystemManager::getSafeString("Enter genre (Pop/Rock/Jazz/etc): ");
        auto recommendations = APIManager::getRecommendations(genre);
        
        if (recommendations.empty()) {
            UI::displayError("No recommendations available!");
            return;
        }
        
        UI::displayMessage("Recommendations for '" + genre + "':");
        UI::displaySeparator();
        
        for (size_t i = 0; i < recommendations.size(); ++i) {
            std::cout << (i + 1) << ". " << recommendations[i]->toString() << "\n";
        }
        
        UI::displaySeparator();
        std::cout << "\nEnter song number to add (0 to skip): ";
        int choice = SystemManager::getSafeInteger(0, recommendations.size());
        
        if (choice > 0 && choice <= (int)recommendations.size()) {
            Song* selected = recommendations[choice - 1];
            playlist.addLast(new Song(selected->getTitle(), selected->getArtist(), selected->getDuration()));
            UI::displaySuccess("Song added to playlist!");
        }
        
        for (auto s : recommendations) {
            delete s;
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}

void MusicPlayer::savePlaylist() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        if (playlist.isEmpty()) {
            UI::displayError("Playlist is empty! Nothing to save.");
            return;
        }
        
        std::string name = SystemManager::getSafeString("Enter playlist name: ");
        
        if (FileManager::savePlaylist(playlist, name)) {
            UI::displaySuccess("Playlist '" + name + "' saved successfully!");
        } else {
            UI::displayError("Failed to save playlist!");
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
}

void MusicPlayer::loadPlaylist() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::string name = SystemManager::getSafeString("Enter playlist name to load: ");
        
        Playlist* loaded = FileManager::loadPlaylist(name);
        
        if (loaded) {
            // Clear current playlist
            playlist.clear();
            
            // Copy songs from loaded playlist
            int size = loaded->getSize();
            for (int i = 0; i < size; ++i) {
                Song* song = loaded->getAt(i);
                if (song) {
                    playlist.addLast(new Song(song->getTitle(), song->getArtist(), song->getDuration()));
                }
            }
            
            delete loaded;
            UI::displaySuccess("Playlist '" + name + "' loaded successfully!");
        } else {
            UI::displayError("Failed to load playlist!");
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
}

void MusicPlayer::viewSavedPlaylists() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        auto playlists = FileManager::listPlaylists();
        
        if (playlists.empty()) {
            UI::displayMessage("No saved playlists found!");
            return;
        }
        
        UI::displayMessage("Saved Playlists:");
        UI::displaySeparator();
        
        for (size_t i = 0; i < playlists.size(); ++i) {
            std::cout << (i + 1) << ". " << playlists[i] << "\n";
        }
        
        UI::displaySeparator();
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}

void MusicPlayer::playSong() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        if (playlist.isEmpty()) {
            UI::displayError("Playlist is empty!");
            return;
        }
        
        std::cout << "Enter song index (0-based): ";
        int index = SystemManager::getSafeInteger(0, playlist.getSize() - 1);
        
        Song* song = playlist.getAt(index);
        if (song) {
            player.play(song);
            UI::displaySuccess("Playing song!");
        } else {
            UI::displayError("Song not found!");
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
}

void MusicPlayer::showNowPlaying() {
    UI::clearScreen();
    player.displayNowPlaying();
}

void MusicPlayer::searchFromLastFM() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        std::string query = SystemManager::getSafeString("Enter song title to search (Last.fm): ");
        auto results = LastFMManager::searchTracks(query);
        
        if (results.empty()) {
            UI::displayError("No tracks found on Last.fm!");
            return;
        }
        
        UI::displayMessage("Last.fm Search Results for '" + query + "':");
        UI::displaySeparator();
        
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << (i + 1) << ". " << results[i]->toString() << "\n";
        }
        
        UI::displaySeparator();
        std::cout << "\nEnter song number to add (0 to skip): ";
        int choice = SystemManager::getSafeInteger(0, results.size());
        
        if (choice > 0 && choice <= (int)results.size()) {
            Song* selected = results[choice - 1];
            playlist.addLast(new Song(selected->getTitle(), selected->getArtist(), selected->getDuration()));
            UI::displaySuccess("Song added from Last.fm!");
        }
        
        for (auto s : results) {
            delete s;
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}

void MusicPlayer::browseLastFMTop() {
    UI::clearScreen();
    UI::displayHeader();
    
    try {
        auto topTracks = LastFMManager::getTopTracks(10);
        
        if (topTracks.empty()) {
            UI::displayError("Could not fetch top tracks!");
            return;
        }
        
        UI::displayMessage("🔥 Last.fm Top Tracks Globally:");
        UI::displaySeparator();
        
        for (size_t i = 0; i < topTracks.size(); ++i) {
            std::cout << (i + 1) << ". " << topTracks[i]->toString() << "\n";
        }
        
        UI::displaySeparator();
        std::cout << "\nEnter song number to add (0 to skip): ";
        int choice = SystemManager::getSafeInteger(0, topTracks.size());
        
        if (choice > 0 && choice <= (int)topTracks.size()) {
            Song* selected = topTracks[choice - 1];
            playlist.addLast(new Song(selected->getTitle(), selected->getArtist(), selected->getDuration()));
            UI::displaySuccess("Track added to your playlist!");
        }
        
        for (auto s : topTracks) {
            delete s;
        }
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
    }
    
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    UI::clearScreen();
}
