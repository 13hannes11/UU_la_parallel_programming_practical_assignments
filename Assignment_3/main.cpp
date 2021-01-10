#include <chrono>
#include <iostream>
#include <stdlib.h>  

#include <lib/ADT_Stack.h>
#include <lib/Stack.cpp>

using namespace std::chrono;

#define DEBUG false

#if DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#define OP_COUNT 100000
#define THREADS 4

std::vector<operation> generate_operations_uniform(){
    operation default_operation = create_operation(methodname::push, 0);
    std::vector<operation> operations(OP_COUNT, default_operation);

    int stack_size = 0;
    for (auto op = operations.begin(); op != operations.end(); op++) {
        switch (rand() % 3) {
            case 0:
                if (stack_size > 0) {
                    op->method = methodname::pop;
                    stack_size--;
                    break;
                }
            case 1:
                op->method = methodname::push;
                op->value = rand() % 20;
                stack_size++;
                break;
            default:
                op->method = methodname::size;
                break;
        }
    }
}

void run_worker(std::vector<operation>* operations, Stack* stack) {    
    std::cout << "Worker: start" << std::endl;
    long op_counter = 0;
    for (operation op : *operations) {
        switch (op.method) {
            case methodname::pop:
                stack->pop();
            break;
            case methodname::push:
                stack->push(op.value);
                break;
            default:
                stack->size();
                break;
        }
    }

     std::cout << "Worker: done" << std::endl;
}

void run_checker(ADTOperationQueue queue, int* done_count) {
    ADTStack * adt_stack = new ADTStack();
    while(true) {
        int finished = *done_count;
        size_t queue_size = queue.size();
        
        if (finished >= THREADS && queue_size == 0) {
            break;
        } else {
            operation op = queue.dequeue();
            adt_stack->do_op(&op);
        }
    }
    std::cout << "Done checking operations" << std::endl;
}

int main(){
    return 0;
}