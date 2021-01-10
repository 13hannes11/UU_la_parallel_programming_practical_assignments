#include <stack>
#include<stdexcept>
#include <sstream>
#include <stdlib.h>

#include "ADT_Stack.h"

operation create_operation(methodname name, int value) {
    operation op;
    op.method = name;
    op.value = value;
    return op;
}


void ADTStack::push(int element){
    stack.push(element);
}

void ADTStack::pop(int output) {
    if (stack.empty() == false) {
        int top = stack.top();
        if (output == top){
            stack.pop();
        } else {
            std::ostringstream oss;
            oss << "Invalid operation: pop " << output << " (actual top: " << top << ")";
            throw std::invalid_argument(oss.str());
        }
    } else {
        std::ostringstream oss;
        oss << "Invalid operation: pop " << output << " (stack is empty)";
        throw std::invalid_argument(oss.str()); 
    }
}

void ADTStack::size(int output){
    int size = stack.size();
    if (output != size) {
        std::ostringstream oss;
        oss << "Invalid operation: size " << output << " (actual size: " << size << ")";
        throw std::invalid_argument(oss.str());
    }
}

void ADTStack::do_op(operation * op) {
    switch (op->method) {
        case methodname::push:
            push(op->value);
            break;
        case methodname::pop:
            pop(op->value);
            break;
        case methodname::size:
            size(op->value);
            break;
        default:
            break;
    }
}

void ADTStack::do_ops(std::vector<operation> ops) {
    for (operation op : ops) {
        do_op(&op);
    }
}

void ADTOperationQueue::enqueue(operation op) {
    mutex.lock();
    queue.push(op);
    mutex.unlock();
}
operation ADTOperationQueue::dequeue() {
    mutex.lock();
    operation op = this->queue.front();
    queue.pop();
    mutex.unlock();
    return op;
}
size_t ADTOperationQueue::size() {
    this->mutex.lock();
    size_t s = queue.size();
    this->mutex.unlock();
    return s;
}

