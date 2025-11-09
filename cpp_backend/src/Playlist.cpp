#include <iostream>
#include "Playlist.hpp"
using std::cout;
using std::endl;
Playlist::Playlist()
{
    head = nullptr;
    tail = nullptr;
    size = 0;
}

bool Playlist::isEmpty() const
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

Song* Playlist::getAt(int index) const
{
    if (isEmpty() || index < 0 || index >= size) return nullptr;
    Node* cur = head;
    for (int i = 0; i < index; ++i) cur = cur->next;
    return cur ? cur->data : nullptr;
}

void Playlist::print() const
{
    if (isEmpty()) {
    cout << "[empty]" << endl;
        return;
    }
    Node* cur = head;
    for (int i = 0; i < size; ++i) {
    cout << i << ": " << cur->data->toString() << endl;
        cur = cur->next;
    }
}

bool Playlist::removeFirst()
{
    if (isEmpty()) return false;
    if (size == 1) {
        delete head;
        head = tail = nullptr;
        size = 0;
        return true;
    }
    Node* oldHead = head;
    head = head->next;
    head->prev = tail;
    tail->next = head;
    delete oldHead;
    --size;
    return true;
}

bool Playlist::removeLast()
{
    if (isEmpty()) return false;
    if (size == 1) return removeFirst();
    Node* oldTail = tail;
    tail = tail->prev;
    tail->next = head;
    head->prev = tail;
    delete oldTail;
    --size;
    return true;
}

bool Playlist::removeIndex(int index)
{
    if (isEmpty()) return false;
    if (index <= 0) return removeFirst();
    if (index >= size - 1) return removeLast();

    Node* cur = head;
    for (int i = 0; i < index; ++i) cur = cur->next;

    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
    --size;
    return true;
}

void Playlist::clear()
{
    while (!isEmpty()) {
        removeFirst();
    }
}

Playlist::~Playlist()
{
    clear();
}