#include "Playlist.hpp"
Playlist::Playlist()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool Playlist::isEmpty()
{
    return head == nullptr;
}

void Playlist::addEmpty(Song *new_song)
{
    Node *new_node = new Node(new_song);
    head = new_node;
    tail = new_node;
    head->next = head;
    head->prev = head;
    size++;
}
void Playlist::addFirst(Song *new_song)
{
    if (new_song == nullptr)
    {
        return;
    }

    if (isEmpty())
    {
        addEmpty(new_song);
    }
    else
    {
        Node *new_node = new Node(new_song);
        new_node->next = head;
        new_node->prev = tail;
        tail->next = new_node;
        head->prev = new_node;
        head = new_node;
        size++;
    }
}

void Playlist::addLast(Song *new_song)
{
    if (new_song == nullptr)
    {
        return;
    }

    if (isEmpty())
    {
        addEmpty(new_song);
    }
    else
    {
        Node *new_node = new Node(new_song);
        new_node->next = head;
        new_node->prev = tail;
        tail->next = new_node;
        head->prev = new_node;
        tail = new_node;
        size++;
    }
}

void Playlist::addIndex(Song *new_song, int index)
{
    if (new_song == nullptr) return;

    // Normalize index to 0-based and clamp to [0, size]
    if (isEmpty()) {
        addEmpty(new_song);
        return;
    }
    if (index <= 0) {
        addFirst(new_song);
        return;
    }
    if (index >= size) {
        addLast(new_song);
        return;
    }

    // Traverse to the node currently at position 'index'
    Node* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }

    Node* new_node = new Node(new_song);
    Node* prev = current->prev;

    // Link prev <-> new_node <-> current
    prev->next = new_node;
    new_node->prev = prev;
    new_node->next = current;
    current->prev = new_node;

    size++;
}

Playlist::~Playlist()
{
    if (isEmpty())
    {
        return;
    }
    head->prev->next = nullptr;
    Node *current = head;

    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}