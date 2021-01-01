#pragma once

#include "Node.cpp"

class Set {
    protected:
        std::string name;
        Set(std::string _name);
        Node* first;
    public:
        bool add(int element) { return false; };
        bool rmv(int element) { return false; };
        bool ctn(int element) { return false; };
        std::string get_name() { return name; };
};

Set::Set(std::string _name){
    name = _name;
    first = Node::Dummy();
    Node* last = Node::Dummy();
    first->next = last;
}

