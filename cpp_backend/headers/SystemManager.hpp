#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include <string>
#include <stdexcept>

/**
 * Custom exception for system errors
 */
class SystemException : public std::runtime_error {
public:
    SystemException(const std::string& message) : std::runtime_error(message) {}
};

/**
 * SystemManager class - Handles system operations and error management
 * Manages input validation, file operations, and error handling
 */
class SystemManager {
public:
    /**
     * Initialize system
     */
    static void initialize();

    /**
     * Shutdown system gracefully
     */
    static void shutdown();

    /**
     * Validate integer input
     */
    static bool validateInteger(int value, int min = INT_MIN, int max = INT_MAX);

    /**
     * Validate string input (not empty)
     */
    static bool validateString(const std::string& str);

    /**
     * Validate duration (seconds)
     */
    static bool validateDuration(int duration);

    /**
     * Validate playlist index
     */
    static bool validateIndex(int index, int size);

    /**
     * Safe input with validation
     */
    static int getSafeInteger(int min = INT_MIN, int max = INT_MAX);

    /**
     * Safe string input
     */
    static std::string getSafeString(const std::string& prompt = "");

    /**
     * Get current system time
     */
    static std::string getSystemTime();

    /**
     * Log message to console
     */
    static void log(const std::string& level, const std::string& message);

    /**
     * Log info level
     */
    static void logInfo(const std::string& message);

    /**
     * Log warning level
     */
    static void logWarning(const std::string& message);

    /**
     * Log error level
     */
    static void logError(const std::string& message);

    /**
     * Log success level
     */
    static void logSuccess(const std::string& message);

    /**
     * Handle exception safely
     */
    static void handleException(const std::exception& e);

private:
    static bool initialized;
};

#endif // SYSTEMMANAGER_HPP
