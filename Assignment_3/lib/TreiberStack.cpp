#include<stdexcept>

#include "TreiberStack.h"
#include "ADT_Stack.h"


TreiberStack::TreiberStack(ADTOperationQueue * queue) : Stack(queue) { 
    count.store(0);
}

void TreiberStack::push(int element) {
    Node * n;
    Node * t;

    while (true) {
        t = top.load(std::memory_order_relaxed);
        n->next = t;
        if (top.compare_exchange_weak(t, n)) {
            op_queue->enqueue(create_operation(methodname::push, element));
            count.fetch_add(1);
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
            count.fetch_add(-1);
            return data;
        }
    }
}
int TreiberStack::size() { 
    int c = count.load(std::memory_order_relaxed);
    op_queue->enqueue(create_operation(methodname::size, c));
    return c;    
}