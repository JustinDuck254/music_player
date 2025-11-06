#include "Playlist.hpp"
Playlist::Playlist(){
    head = nullptr;
    tail = nullptr;
}

bool Playlist::isEmpty(){
    return head==nullptr;
}
void Playlist::addFirst(Song* new_song){
    if(new_song == nullptr){
        return;
    }
    Node* new_node = new Node(new_song);
    
    if(isEmpty()){
        head = new_node;
        tail = new_node;
        head->next = head;
        head->prev = head;
    } else {
        new_node->next = head;
        new_node->prev = tail;
        tail->next = new_node;
        head->prev = new_node;
        head = new_node;
    }
}

void Playlist::addLast(Song* new_song){
    if(new_song == nullptr){
        return;
    }
    Node* new_node = new Node(new_song);
    
    if(isEmpty()){
        head = new_node;
        tail = new_node;
        head->next = head;
        head->prev = head;
    } else {
        new_node->next = head;
        new_node->prev = tail;
        tail->next = new_node;
        head->prev = new_node;
        tail = new_node;
    }
}


Playlist::~Playlist(){
    if(isEmpty()){
        return;
    }
    head->prev->next = nullptr;
    Node* current = head;

    while(current!=nullptr){
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}