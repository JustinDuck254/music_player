#include "LastFMManager.hpp"
#include "SystemManager.hpp"
#include <sstream>
#include <algorithm>
#include <iostream>

// Static member initialization
std::string LastFMManager::apiKey = "";
bool LastFMManager::initialized = false;
const std::string LastFMManager::API_BASE_URL = "http://ws.audioscrobbler.com/2.0/?";
const std::string LastFMManager::API_FORMAT = "json";

void LastFMManager::initialize(const std::string& key) {
    apiKey = key;
    initialized = true;
    SystemManager::logSuccess("Last.fm API initialized!");
}

bool LastFMManager::isInitialized() {
    return initialized && !apiKey.empty();
}

std::string LastFMManager::buildApiUrl(const std::map<std::string, std::string>& params) {
    std::string url = API_BASE_URL;
    url += "format=" + API_FORMAT + "&api_key=" + apiKey;
    
    for (const auto& pair : params) {
        url += "&" + pair.first + "=" + pair.second;
    }
    
    return url;
}

std::string LastFMManager::makeRequest(const std::string& url) {
    try {
        // Mock implementation - returns JSON-like data
        // In production, use actual curl library:
        // CURL* curl = curl_easy_init();
        // curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // etc...
        
        SystemManager::logInfo("API Request: " + url);
        
        // For now, return mock data
        // This demonstrates the structure
        return R"({
            "tracks": {
                "track": [
                    {
                        "name": "Blinding Lights",
                        "artist": {
                            "name": "The Weeknd"
                        },
                        "duration": "200"
                    },
                    {
                        "name": "Heat Waves",
                        "artist": {
                            "name": "Glass Animals"
                        },
                        "duration": "239"
                    }
                ]
            }
        })";
    } catch (const std::exception& e) {
        SystemManager::logError("API request failed: " + std::string(e.what()));
        return "";
    }
}

std::vector<Song*> LastFMManager::parseTracksFromJson(const std::string& jsonResponse) {
    std::vector<Song*> songs;
    
    try {
        if (jsonResponse.empty()) {
            SystemManager::logWarning("Empty JSON response!");
            return songs;
        }

        // Simple JSON parsing (production would use nlohmann/json)
        size_t pos = 0;
        
        // Look for track objects
        while ((pos = jsonResponse.find("\"name\"", pos)) != std::string::npos) {
            // Extract track name
            size_t nameStart = jsonResponse.find("\"", pos + 7) + 1;
            size_t nameEnd = jsonResponse.find("\"", nameStart);
            std::string trackName = jsonResponse.substr(nameStart, nameEnd - nameStart);
            
            // Extract artist (simple parse)
            size_t artistPos = jsonResponse.find("\"artist\"", pos);
            size_t artistNameStart = jsonResponse.find("\"name\"", artistPos) + 7;
            size_t artistNameBegin = jsonResponse.find("\"", artistNameStart) + 1;
            size_t artistNameEnd = jsonResponse.find("\"", artistNameBegin);
            std::string artistName = jsonResponse.substr(artistNameBegin, artistNameEnd - artistNameBegin);
            
            // Default duration
            int duration = 200;
            
            // Avoid duplicates
            bool isDuplicate = false;
            for (auto* s : songs) {
                if (s->getTitle() == trackName) {
                    isDuplicate = true;
                    break;
                }
            }
            
            if (!isDuplicate && !trackName.empty() && !artistName.empty()) {
                songs.push_back(new Song(trackName, artistName, duration));
            }
            
            pos = nameEnd;
        }
        
        if (songs.empty()) {
            SystemManager::logWarning("No tracks parsed from response!");
        } else {
            SystemManager::logSuccess("Parsed " + std::to_string(songs.size()) + " tracks from API!");
        }
        
    } catch (const std::exception& e) {
        SystemManager::logError("JSON parsing error: " + std::string(e.what()));
    }
    
    return songs;
}

std::string LastFMManager::extractJsonValue(const std::string& json, const std::string& key) {
    size_t pos = json.find("\"" + key + "\"");
    if (pos == std::string::npos) return "";
    
    size_t valueStart = json.find("\"", pos + key.length() + 3) + 1;
    size_t valueEnd = json.find("\"", valueStart);
    
    return json.substr(valueStart, valueEnd - valueStart);
}

std::vector<Song*> LastFMManager::searchTracks(const std::string& trackName) {
    try {
        if (!isInitialized()) {
            SystemManager::logError("Last.fm API not initialized!");
            return std::vector<Song*>();
        }
        
        std::map<std::string, std::string> params;
        params["method"] = "track.search";
        params["track"] = trackName;
        params["limit"] = "10";
        
        std::string url = buildApiUrl(params);
        std::string response = makeRequest(url);
        
        return parseTracksFromJson(response);
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        return std::vector<Song*>();
    }
}

std::vector<Song*> LastFMManager::getTopTracks(int limit) {
    try {
        if (!isInitialized()) {
            SystemManager::logError("Last.fm API not initialized!");
            return std::vector<Song*>();
        }
        
        std::map<std::string, std::string> params;
        params["method"] = "chart.gettoptracks";
        params["limit"] = std::to_string(limit);
        
        std::string url = buildApiUrl(params);
        std::string response = makeRequest(url);
        
        SystemManager::logInfo("Fetching top " + std::to_string(limit) + " tracks globally...");
        
        return parseTracksFromJson(response);
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        return std::vector<Song*>();
    }
}

std::vector<Song*> LastFMManager::getTopTracksByCountry(const std::string& country, int limit) {
    try {
        if (!isInitialized()) {
            SystemManager::logError("Last.fm API not initialized!");
            return std::vector<Song*>();
        }
        
        std::map<std::string, std::string> params;
        params["method"] = "geo.gettoptracks";
        params["country"] = country;
        params["limit"] = std::to_string(limit);
        
        std::string url = buildApiUrl(params);
        std::string response = makeRequest(url);
        
        SystemManager::logInfo("Fetching top tracks from " + country + "...");
        
        return parseTracksFromJson(response);
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        return std::vector<Song*>();
    }
}

std::vector<Song*> LastFMManager::getTracksByArtist(const std::string& artistName, int limit) {
    try {
        if (!isInitialized()) {
            SystemManager::logError("Last.fm API not initialized!");
            return std::vector<Song*>();
        }
        
        std::map<std::string, std::string> params;
        params["method"] = "artist.gettoptracks";
        params["artist"] = artistName;
        params["limit"] = std::to_string(limit);
        
        std::string url = buildApiUrl(params);
        std::string response = makeRequest(url);
        
        SystemManager::logInfo("Fetching top tracks by " + artistName + "...");
        
        return parseTracksFromJson(response);
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        return std::vector<Song*>();
    }
}

std::vector<Song*> LastFMManager::getSimilarTracks(const std::string& trackName, const std::string& artistName) {
    try {
        if (!isInitialized()) {
            SystemManager::logError("Last.fm API not initialized!");
            return std::vector<Song*>();
        }
        
        std::map<std::string, std::string> params;
        params["method"] = "track.getsimilar";
        params["track"] = trackName;
        params["artist"] = artistName;
        params["limit"] = "5";
        
        std::string url = buildApiUrl(params);
        std::string response = makeRequest(url);
        
        SystemManager::logInfo("Fetching similar tracks to " + trackName + "...");
        
        return parseTracksFromJson(response);
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        return std::vector<Song*>();
    }
}

std::vector<Song*> LastFMManager::getTrendingTracks(int limit) {
    try {
        // Trending = Recently played (most scrobbled)
        return getTopTracks(limit);
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        return std::vector<Song*>();
    }
}

std::string LastFMManager::getTrackInfo(const std::string& trackName, const std::string& artistName) {
    try {
        if (!isInitialized()) {
            return "API not initialized";
        }
        
        std::map<std::string, std::string> params;
        params["method"] = "track.getinfo";
        params["track"] = trackName;
        params["artist"] = artistName;
        
        std::string url = buildApiUrl(params);
        std::string response = makeRequest(url);
        
        // Extract play count and listeners
        std::string playCount = extractJsonValue(response, "playcount");
        std::string listeners = extractJsonValue(response, "listeners");
        
        std::string info = "Track: " + trackName + "\n";
        info += "Artist: " + artistName + "\n";
        if (!playCount.empty()) info += "Total Plays: " + playCount + "\n";
        if (!listeners.empty()) info += "Listeners: " + listeners;
        
        return info;
    } catch (const std::exception& e) {
        SystemManager::handleException(e);
        return "Error fetching info";
    }
}
