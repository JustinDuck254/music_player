#ifndef UI_HPP
#define UI_HPP

#include <string>

/**
 * UI class - Handles user interface and console display
 * Provides menu display and input handling
 */
class UI {
public:
    /**
     * Display main menu
     */
    static void displayMainMenu();

    /**
     * Display playlist menu
     */
    static void displayPlaylistMenu();

    /**
     * Display separator line
     */
    static void displaySeparator();

    /**
     * Display header
     */
    static void displayHeader();

    /**
     * Get user's menu choice
     */
    static int getUserChoice();

    /**
     * Get song title from user
     */
    static std::string getSongTitle();

    /**
     * Get artist name from user
     */
    static std::string getArtistName();

    /**
     * Get song duration from user
     */
    static int getSongDuration();

    /**
     * Get index from user
     */
    static int getIndex();

    /**
     * Display message
     */
    static void displayMessage(const std::string& message);

    /**
     * Display error message
     */
    static void displayError(const std::string& error);

    /**
     * Display success message
     */
    static void displaySuccess(const std::string& success);

    /**
     * Clear screen
     */
    static void clearScreen();
};

#endif // UI_HPP
