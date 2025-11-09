#ifndef LASTFMMANAGER_HPP
#define LASTFMMANAGER_HPP

#include "Song.hpp"
#include <vector>
#include <string>
#include <map>

/**
 * LastFMManager - Integrates with Last.fm API
 * Fetches real music data from Last.fm database
 * Note: Requires curl library and internet connection
 */
class LastFMManager {
public:
    /**
     * Initialize LastFM API (set API key)
     */
    static void initialize(const std::string& apiKey);

    /**
     * Search tracks by name (real Last.fm data)
     */
    static std::vector<Song*> searchTracks(const std::string& trackName);

    /**
     * Get top tracks globally
     */
    static std::vector<Song*> getTopTracks(int limit = 10);

    /**
     * Get top tracks by country
     */
    static std::vector<Song*> getTopTracksByCountry(const std::string& country, int limit = 10);

    /**
     * Get tracks by artist
     */
    static std::vector<Song*> getTracksByArtist(const std::string& artistName, int limit = 10);

    /**
     * Get similar tracks based on a track
     */
    static std::vector<Song*> getSimilarTracks(const std::string& trackName, const std::string& artistName);

    /**
     * Get trending tracks (most played recently)
     */
    static std::vector<Song*> getTrendingTracks(int limit = 10);

    /**
     * Get track info including play count
     */
    static std::string getTrackInfo(const std::string& trackName, const std::string& artistName);

    /**
     * Check if API is initialized
     */
    static bool isInitialized();

    /**
     * Format URL with parameters for API call
     */
    static std::string buildApiUrl(const std::map<std::string, std::string>& params);

private:
    static std::string apiKey;
    static bool initialized;
    static const std::string API_BASE_URL;
    static const std::string API_FORMAT;

    /**
     * Make HTTP GET request
     */
    static std::string makeRequest(const std::string& url);

    /**
     * Parse JSON response
     */
    static std::vector<Song*> parseTracksFromJson(const std::string& jsonResponse);

    /**
     * Extract value from simple JSON
     */
    static std::string extractJsonValue(const std::string& json, const std::string& key);
};

#endif // LASTFMMANAGER_HPP
