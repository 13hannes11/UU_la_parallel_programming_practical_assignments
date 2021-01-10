#include "Stack.h"
#include "Node.h"

#include <iostream>
#include<sstream>

Stack::Stack(ADTOperationQueue * queue){
    op_queue = queue;
}

void Stack::push(int element) { return; }
int Stack::pop() { return 0; }
int Stack::size() { return 0; }

std::string Stack::print_stack(){ return ""; }
