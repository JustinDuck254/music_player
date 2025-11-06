#pragma once
#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP
#include "Node.hpp"

//Circular Double Linked List
class Playlist{ 
    private:
        Node* head;
        Node* tail;
    public:
        Playlist();
        bool isEmpty();
        void addFirst(Song* new_song);
        void addLast(Song* new_song);

        void addindex(Song* new_song, int index);

        ~Playlist();
};
#endif