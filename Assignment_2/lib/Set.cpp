#include "Set.h"
#include "Node.h"

#include <iostream>
#include<sstream>

Set::Set(std::string _name){
    name = _name;
    first = Node::Dummy();
    first->next = Node::Dummy();
}

bool Set::add(int element) { return false; }
bool Set::rmv(int element) { return false; }
bool Set::ctn(int element) { return false; }
std::string Set::get_name() { return name; }

std::string Set::print_set(){
    Node* c = this->first->next;
    std::stringstream ss;
    while (!c->is_dummy()) {
        ss << c->get_data() << " ";
        c = c->next;
    }
    return ss.str();
}
