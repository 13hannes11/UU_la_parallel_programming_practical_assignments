#include "SimpleLockingStack.h"
#include "ADT_Stack.h"

SimpleLockingStack::SimpleLockingStack(ADTOperationQueue * queue) : Stack(queue) { }

void SimpleLockingStack::push(int element) { 
    mut.lock();
    vec.push_back(element);
    op_queue->enqueue(create_operation(methodname::push, element));
    mut.unlock();
}
int SimpleLockingStack::pop() {
    mut.lock();
    int e = vec.back();
    vec.pop_back();
    op_queue->enqueue(create_operation(methodname::pop, e));
    mut.unlock();
    return e;
}
int SimpleLockingStack::size() { 
    mut.lock();
    int s = vec.size();
    op_queue->enqueue(create_operation(methodname::size, s));
    mut.unlock();
    return s;    
}