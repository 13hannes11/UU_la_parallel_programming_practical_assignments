#include "Set.h"
#include "Node.h"

Set::Set(std::string _name){
    name = _name;
    first = Node::Dummy();
    first->next = Node::Dummy();
}

bool Set::add(int element) { return false; }
bool Set::rmv(int element) { return false; }
bool Set::ctn(int element) { return false; }
std::string Set::get_name() { return name; }
