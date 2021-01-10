#include "Stack.h"
#include "Node.h"

#include <iostream>
#include<sstream>

Stack::Stack(ADTOperationQueue * queue){
    first = Node::Dummy();
    first->next = Node::Dummy();
    op_queue = queue;
}

void Stack::push(int element) { return; }
int Stack::pop() { return 0; }
int Stack::size() { return 0; }

std::string Stack::print_stack(){
    Node* c = this->first->next;
    std::stringstream ss;
    while (!c->is_dummy()) {
        ss << c->get_data() << " ";
        c = c->next;
    }
    return ss.str();
}
