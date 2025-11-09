#include "SystemManager.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <limits>
#include <ctime>

bool SystemManager::initialized = false;

void SystemManager::initialize() {
    if (initialized) return;
    
    initialized = true;
    logSuccess("System initialized successfully!");
}

void SystemManager::shutdown() {
    if (!initialized) return;
    
    logInfo("System shutting down...");
    initialized = false;
}

bool SystemManager::validateInteger(int value, int min, int max) {
    return value >= min && value <= max;
}

bool SystemManager::validateString(const std::string& str) {
    return !str.empty() && str.length() > 0;
}

bool SystemManager::validateDuration(int duration) {
    return duration > 0 && duration <= 3600; // Max 1 hour
}

bool SystemManager::validateIndex(int index, int size) {
    return index >= 0 && index < size;
}

int SystemManager::getSafeInteger(int min, int max) {
    int value;
    
    while (true) {
        std::cin >> value;
        
        // Clear input buffer in case of invalid input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            logWarning("Invalid input! Please enter a valid integer.");
            continue;
        }
        
        std::cin.ignore(); // Clear newline from buffer
        
        if (validateInteger(value, min, max)) {
            return value;
        } else {
            logWarning("Value out of range! Please enter a value between " + 
                      std::to_string(min) + " and " + std::to_string(max) + ".");
        }
    }
}

std::string SystemManager::getSafeString(const std::string& prompt) {
    std::string input;
    
    while (true) {
        if (!prompt.empty()) {
            std::cout << prompt;
        }
        
        std::getline(std::cin, input);
        
        if (validateString(input)) {
            return input;
        } else {
            logWarning("Input cannot be empty! Please try again.");
        }
    }
}

std::string SystemManager::getSystemTime() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    
    return oss.str();
}

void SystemManager::log(const std::string& level, const std::string& message) {
    std::cout << "[" << getSystemTime() << "] [" << level << "] " << message << "\n";
}

void SystemManager::logInfo(const std::string& message) {
    log("INFO", message);
}

void SystemManager::logWarning(const std::string& message) {
    log("WARNING", message);
}

void SystemManager::logError(const std::string& message) {
    log("ERROR", message);
}

void SystemManager::logSuccess(const std::string& message) {
    log("SUCCESS", message);
}

void SystemManager::handleException(const std::exception& e) {
    logError("Exception occurred: " + std::string(e.what()));
}
