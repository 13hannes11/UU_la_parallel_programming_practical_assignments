#pragma once

#include "Node.h"

class Stack {
    protected:
        std::string name;
        Stack(std::string _name);
        Node* first;
    public:
        bool push(int element);
        bool pop(int element);
        bool size(int element);
        std::string print_stack();
};