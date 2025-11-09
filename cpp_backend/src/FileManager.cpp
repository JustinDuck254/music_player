#include "FileManager.hpp"
#include "SystemManager.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::string FileManager::getPlaylistsDirectory() {
    std::string homeDir = std::getenv("USERPROFILE");
    return homeDir + "\\Music\\MusicPlayer\\Playlists";
}

void FileManager::ensureDirectoryExists() {
    std::string dir = getPlaylistsDirectory();
    try {
        if (!fs::exists(dir)) {
            fs::create_directories(dir);
            SystemManager::logSuccess("Playlists directory created!");
        }
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to create directory: " + std::string(e.what()));
    }
}

bool FileManager::fileExists(const std::string& filename) {
    try {
        std::string fullPath = getPlaylistsDirectory() + "\\" + filename + ".json";
        return fs::exists(fullPath);
    } catch (...) {
        return false;
    }
}

bool FileManager::savePlaylist(const Playlist& playlist, const std::string& filename) {
    try {
        ensureDirectoryExists();
        
        std::string fullPath = getPlaylistsDirectory() + "\\" + filename + ".json";
        std::ofstream file(fullPath);
        
        if (!file.is_open()) {
            SystemManager::logError("Failed to open file for writing: " + fullPath);
            return false;
        }
        
        // Write JSON header
        file << "{\n";
        file << "  \"playlist_name\": \"" << filename << "\",\n";
        file << "  \"created_at\": \"" << SystemManager::getSystemTime() << "\",\n";
        file << "  \"songs\": [\n";
        
        // Write songs (simplified - in production use actual JSON library)
        int size = playlist.getSize();
        for (int i = 0; i < size; ++i) {
            Song* song = playlist.getAt(i);
            if (song) {
                file << "    {\n";
                file << "      \"title\": \"" << song->getTitle() << "\",\n";
                file << "      \"artist\": \"" << song->getArtist() << "\",\n";
                file << "      \"duration\": " << song->getDuration() << "\n";
                file << "    }";
                
                if (i < size - 1) {
                    file << ",";
                }
                file << "\n";
            }
        }
        
        file << "  ]\n";
        file << "}\n";
        
        file.close();
        SystemManager::logSuccess("Playlist saved to: " + fullPath);
        return true;
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to save playlist: " + std::string(e.what()));
        return false;
    }
}

Playlist* FileManager::loadPlaylist(const std::string& filename) {
    try {
        std::string fullPath = getPlaylistsDirectory() + "\\" + filename + ".json";
        
        if (!fileExists(filename)) {
            SystemManager::logWarning("Playlist file not found: " + fullPath);
            return nullptr;
        }
        
        std::ifstream file(fullPath);
        if (!file.is_open()) {
            SystemManager::logError("Failed to open file for reading: " + fullPath);
            return nullptr;
        }
        
        Playlist* playlist = new Playlist();
        std::string line;
        std::string title, artist;
        int duration;
        
        // Simple JSON parsing (in production use nlohmann/json)
        while (std::getline(file, line)) {
            if (line.find("\"title\": \"") != std::string::npos) {
                size_t start = line.find("\"") + 1;
                size_t end = line.rfind("\"");
                title = line.substr(start, end - start);
            }
            else if (line.find("\"artist\": \"") != std::string::npos) {
                size_t start = line.find("\"") + 1;
                size_t end = line.rfind("\"");
                artist = line.substr(start, end - start);
            }
            else if (line.find("\"duration\": ") != std::string::npos) {
                size_t start = line.find(": ") + 2;
                duration = std::stoi(line.substr(start));
                
                // Add song to playlist
                playlist->addLast(new Song(title, artist, duration));
            }
        }
        
        file.close();
        SystemManager::logSuccess("Playlist loaded from: " + fullPath);
        return playlist;
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to load playlist: " + std::string(e.what()));
        return nullptr;
    }
}

bool FileManager::deleteFile(const std::string& filename) {
    try {
        std::string fullPath = getPlaylistsDirectory() + "\\" + filename + ".json";
        
        if (fs::remove(fullPath)) {
            SystemManager::logSuccess("Playlist deleted: " + fullPath);
            return true;
        } else {
            SystemManager::logWarning("File not found: " + fullPath);
            return false;
        }
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to delete file: " + std::string(e.what()));
        return false;
    }
}

std::vector<std::string> FileManager::listPlaylists() {
    std::vector<std::string> playlists;
    
    try {
        std::string dir = getPlaylistsDirectory();
        
        if (!fs::exists(dir)) {
            SystemManager::logWarning("Playlists directory does not exist!");
            return playlists;
        }
        
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.is_regular_file() && entry.path().extension() == ".json") {
                std::string filename = entry.path().stem().string();
                playlists.push_back(filename);
            }
        }
        
        if (!playlists.empty()) {
            SystemManager::logSuccess("Found " + std::to_string(playlists.size()) + " saved playlists!");
        }
    } catch (const std::exception& e) {
        SystemManager::logError("Failed to list playlists: " + std::string(e.what()));
    }
    
    return playlists;
}
