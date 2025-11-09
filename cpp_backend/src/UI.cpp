#include "UI.hpp"
#include <iostream>
#include <string>

void UI::clearScreen() {
    system("cls");
}

void UI::displayHeader() {
    std::cout << "\n";
    displaySeparator();
    std::cout << "         === MUSIC PLAYER ===\n";
    displaySeparator();
}

void UI::displaySeparator() {
    std::cout << "========================================\n";
}

void UI::displayMainMenu() {
    displayHeader();
    std::cout << "\n[1] Add Song to End\n";
    std::cout << "[2] Add Song at Beginning\n";
    std::cout << "[3] Add Song at Position\n";
    std::cout << "[4] View Playlist\n";
    std::cout << "[5] Remove First Song\n";
    std::cout << "[6] Remove Last Song\n";
    std::cout << "[7] Remove Song at Position\n";
    std::cout << "[8] Get Song at Position\n";
    std::cout << "[9] Clear Playlist\n";
    std::cout << "[0] Exit\n";
    displaySeparator();
}

void UI::displayPlaylistMenu() {
    std::cout << "\n--- Playlist Menu ---\n";
    displaySeparator();
}

void UI::displayMessage(const std::string& message) {
    std::cout << "\n" << message << "\n";
}

void UI::displayError(const std::string& error) {
    std::cout << "\n[ERROR] " << error << "\n";
}

void UI::displaySuccess(const std::string& success) {
    std::cout << "\n[SUCCESS] " << success << "\n";
}

int UI::getUserChoice() {
    int choice;
    std::cout << "\nEnter choice: ";
    std::cin >> choice;
    std::cin.ignore(); // Clear input buffer
    return choice;
}

std::string UI::getSongTitle() {
    std::string title;
    std::cout << "Enter song title: ";
    std::getline(std::cin, title);
    return title;
}

std::string UI::getArtistName() {
    std::string artist;
    std::cout << "Enter artist name: ";
    std::getline(std::cin, artist);
    return artist;
}

int UI::getSongDuration() {
    int duration;
    std::cout << "Enter duration (seconds): ";
    std::cin >> duration;
    std::cin.ignore(); // Clear input buffer
    return duration;
}

int UI::getIndex() {
    int index;
    std::cout << "Enter position (0-based): ";
    std::cin >> index;
    std::cin.ignore(); // Clear input buffer
    return index;
}
