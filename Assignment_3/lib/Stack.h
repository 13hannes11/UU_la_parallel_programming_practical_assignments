#pragma once

#include "Node.h"
#include "ADT_Stack.h"

class Stack {
    protected:
        ADTOperationQueue * op_queue;
        Stack(ADTOperationQueue * queue);
        Node* first;
    public:
        bool push(int element);
        bool pop(int element);
        bool size(int element);
        std::string print_stack();
};