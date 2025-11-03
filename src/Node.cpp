#include "Node.hpp"

Node::Node(Song* data){
    this->data = data;
}

Node::Node(Song* data, Node* next ){
    this->data = data;
    this->next = next;
}

Node::Node(Song* data,Node* next,Node* prev){
    this->data = data;
    this->next = next;
    this->prev = prev;
}

Node::~Node(){
    delete data;
}