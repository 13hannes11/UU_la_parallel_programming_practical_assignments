#pragma once

#include "Node.h"
#include "ADT_Stack.h"

class Stack {
    protected:
        ADTOperationQueue * op_queue;
        Stack(ADTOperationQueue * queue);
        Node* first;
    public:
        void push(int element);
        int pop();
        int size();
        std::string print_stack();
};