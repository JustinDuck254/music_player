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
        void addFirst(Node* new_node);
};
#endif