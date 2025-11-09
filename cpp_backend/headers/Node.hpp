#pragma once
#ifndef NODE_H
#define NODE_H
#include "Song.hpp"
class Node
{
private:
    Song *data;
    Node *prev, *next;

public:
    friend class Playlist;
    Node(Song *data);
    Node(Song *data, Node *next);
    Node(Song *data, Node *next, Node *prev);

    ~Node();
};

#endif