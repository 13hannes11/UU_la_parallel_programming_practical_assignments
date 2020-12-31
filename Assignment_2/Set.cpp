#pragma once

#include "Node.cpp"

class Set {
    protected:
        Set();
        Node* first;
    public:
        virtual bool add(int element);
        virtual bool rmv(int element);
        virtual bool ctn(int element);
};

Set::Set(){
    first = Node::Dummy(); // dummy node;
    Node* last = Node::Dummy();
    first->next = last;
}