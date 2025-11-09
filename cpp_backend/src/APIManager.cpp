#include "APIManager.hpp"
#include "SystemManager.hpp"
#include <algorithm>

std::vector<Song*> APIManager::fetchPopularSongs() {
    try {
        SystemManager::logInfo("Fetching popular songs from database...");
        auto songs = getMockDatabase();
        SystemManager::logSuccess("Popular songs fetched successfully!");
        return songs;
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to fetch popular songs!");
        return std::vector<Song*>();
    }
}

std::vector<Song*> APIManager::searchSongs(const std::string& query) {
    try {
        SystemManager::logInfo("Searching songs: '" + query + "'");
        auto allSongs = getMockDatabase();
        std::vector<Song*> results;
        
        for (auto song : allSongs) {
            std::string title = song->getTitle();
            // Convert to lowercase for case-insensitive search
            std::transform(title.begin(), title.end(), title.begin(), ::tolower);
            std::string searchQuery = query;
            std::transform(searchQuery.begin(), searchQuery.end(), searchQuery.begin(), ::tolower);
            
            if (title.find(searchQuery) != std::string::npos) {
                results.push_back(new Song(*song));
            }
        }
        
        if (!results.empty()) {
            SystemManager::logSuccess("Found " + std::to_string(results.size()) + " songs!");
        } else {
            SystemManager::logWarning("No songs found matching: '" + query + "'");
        }
        
        // Clean up allSongs
        for (auto s : allSongs) {
            delete s;
        }
        
        return results;
    } catch (const std::exception& e) {
        SystemManager::logError("Search error!");
        return std::vector<Song*>();
    }
}

std::vector<Song*> APIManager::searchByArtist(const std::string& artist) {
    try {
        SystemManager::logInfo("Searching songs by artist: '" + artist + "'");
        auto allSongs = getMockDatabase();
        std::vector<Song*> results;
        
        for (auto song : allSongs) {
            std::string songArtist = song->getArtist();
            std::transform(songArtist.begin(), songArtist.end(), songArtist.begin(), ::tolower);
            std::string searchArtist = artist;
            std::transform(searchArtist.begin(), searchArtist.end(), searchArtist.begin(), ::tolower);
            
            if (songArtist.find(searchArtist) != std::string::npos) {
                results.push_back(new Song(*song));
            }
        }
        
        if (!results.empty()) {
            SystemManager::logSuccess("Found " + std::to_string(results.size()) + " songs by artist!");
        } else {
            SystemManager::logWarning("No songs found by artist: '" + artist + "'");
        }
        
        for (auto s : allSongs) {
            delete s;
        }
        
        return results;
    } catch (const std::exception& e) {
        SystemManager::logError("Artist search error!");
        return std::vector<Song*>();
    }
}

std::vector<Song*> APIManager::getTrendingSongs() {
    try {
        SystemManager::logInfo("Fetching trending songs...");
        auto songs = getMockDatabase();
        
        // Return top 5 trending (mock: first 5)
        std::vector<Song*> trending(songs.begin(), songs.begin() + std::min(5, (int)songs.size()));
        
        SystemManager::logSuccess("Trending songs fetched!");
        return trending;
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to fetch trending songs!");
        return std::vector<Song*>();
    }
}

std::vector<Song*> APIManager::getRecommendations(const std::string& genre) {
    try {
        SystemManager::logInfo("Getting recommendations for genre: '" + genre + "'");
        auto allSongs = getMockDatabase();
        
        // Mock: return random 3 songs (in real implementation, filter by genre)
        std::vector<Song*> recommendations(allSongs.begin(), allSongs.begin() + std::min(3, (int)allSongs.size()));
        
        SystemManager::logSuccess("Recommendations fetched!");
        return recommendations;
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to fetch recommendations!");
        return std::vector<Song*>();
    }
}

std::vector<Song*> APIManager::getMockDatabase() {
    std::vector<Song*> songs;
    
    // Popular songs database
    songs.push_back(new Song("Blinding Lights", "The Weeknd", 200));
    songs.push_back(new Song("Shape of You", "Ed Sheeran", 233));
    songs.push_back(new Song("Someone Like You", "Adele", 285));
    songs.push_back(new Song("Bad Guy", "Billie Eilish", 194));
    songs.push_back(new Song("Perfect", "Ed Sheeran", 263));
    songs.push_back(new Song("Uptown Funk", "Bruno Mars", 269));
    songs.push_back(new Song("Levitating", "Dua Lipa", 203));
    songs.push_back(new Song("Anti-Hero", "Taylor Swift", 228));
    songs.push_back(new Song("Heat Waves", "Glass Animals", 239));
    songs.push_back(new Song("As It Was", "Harry Styles", 183));
    
    return songs;
}
