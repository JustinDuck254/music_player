#pragma once
#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP
#include "Node.hpp"

// Circular Double Linked List
class Playlist
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    Playlist();
    bool isEmpty();
    void addEmpty(Song *new_song);
    void addFirst(Song *new_song);
    void addLast(Song *new_song);

    void addIndex(Song *new_song, int index);
    int getSize() const { return size; }

    ~Playlist();
};
#endif