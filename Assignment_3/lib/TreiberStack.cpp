#include<stdexcept>

#include "TreiberStack.h"
#include "ADT_Stack.h"


TreiberStack::TreiberStack(ADTOperationQueue * queue) : Stack(queue) { }

void TreiberStack::push(int element) {
    Node * n;
    Node * t;

    while (true) {
        t = top.load(std::memory_order_relaxed);
        n->next = t;
        if (top.compare_exchange_weak(t, n)) {
            op_queue->enqueue(create_operation(methodname::push, element));
            return;
        }
    }
    
}
int TreiberStack::pop() {
    Node * n;
    Node * t;

    while (true) {
        t = top.load(std::memory_order_relaxed);
        if (t == NULL) {
            throw std::invalid_argument("Invalid operation: pop on an empty stack");
        } else if (top.compare_exchange_weak(t, t->next)) {
            int data = t->get_data();
            op_queue->enqueue(create_operation(methodname::pop, data));
            return data;
        }
    }
}
int TreiberStack::size() { 
    return 0;    
}