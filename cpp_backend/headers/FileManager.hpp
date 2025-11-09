#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "Playlist.hpp"
#include <string>
#include <vector>

/**
 * FileManager class - Handles file I/O operations
 * Saves and loads playlists in JSON format
 */
class FileManager {
public:
    /**
     * Save playlist to file
     */
    static bool savePlaylist(const Playlist& playlist, const std::string& filename);

    /**
     * Load playlist from file
     */
    static Playlist* loadPlaylist(const std::string& filename);

    /**
     * Check if file exists
     */
    static bool fileExists(const std::string& filename);

    /**
     * Delete file
     */
    static bool deleteFile(const std::string& filename);

    /**
     * Get list of all saved playlists
     */
    static std::vector<std::string> listPlaylists();

    /**
     * Get default playlists directory
     */
    static std::string getPlaylistsDirectory();

private:
    /**
     * Ensure playlists directory exists
     */
    static void ensureDirectoryExists();
};

#endif // FILEMANAGER_HPP
