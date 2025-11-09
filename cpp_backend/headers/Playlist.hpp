#pragma once
#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP
#include "Node.hpp"

// Circular Doubly Linked List for songs
class Playlist
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    Playlist();
    bool isEmpty() const;
    void addEmpty(Song *new_song);
    void addFirst(Song *new_song);
    void addLast(Song *new_song);

    void addIndex(Song *new_song, int index);
    int getSize() const { return size; }

    // Access & utilities
    Song* getAt(int index) const; // 0-based, returns nullptr if out of range
    void print() const;           // Print all songs in order
    void clear();                 // Clear entire playlist

    // Remove operations
    bool removeFirst();
    bool removeLast();
    bool removeIndex(int index); // 0-based

    ~Playlist();
};
#endif