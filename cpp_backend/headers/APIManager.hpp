#ifndef APIMANAGER_HPP
#define APIMANAGER_HPP

#include "Song.hpp"
#include <vector>
#include <string>

/**
 * APIManager class - Handles API calls and data fetching
 * Currently uses mock data; can be extended for real APIs
 */
class APIManager {
public:
    /**
     * Fetch songs from API (currently mock data)
     * Can be extended to call real APIs like Spotify, LastFM, etc.
     */
    static std::vector<Song*> fetchPopularSongs();

    /**
     * Search songs by title
     */
    static std::vector<Song*> searchSongs(const std::string& query);

    /**
     * Search songs by artist
     */
    static std::vector<Song*> searchByArtist(const std::string& artist);

    /**
     * Get trending songs
     */
    static std::vector<Song*> getTrendingSongs();

    /**
     * Get recommended songs based on genre
     */
    static std::vector<Song*> getRecommendations(const std::string& genre);

private:
    /**
     * Generate mock song database
     */
    static std::vector<Song*> getMockDatabase();
};

#endif // APIMANAGER_HPP
