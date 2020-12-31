#pragma once

#include "Node.cpp"

class Set {
    protected:
        Set();
        Node* first;
    public:
        bool add(int element) { return false; };
        bool rmv(int element) { return false; };
        bool ctn(int element) { return false; };
};

Set::Set(){
    first = Node::Dummy();
    Node* last = Node::Dummy();
    first->next = last;
}