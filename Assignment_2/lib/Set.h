#pragma once

#include "Node.h"

class Set {
    protected:
        std::string name;
        Set(std::string _name);
        Node* first;
    public:
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
        std::string get_name();
        std::string print_set();
};