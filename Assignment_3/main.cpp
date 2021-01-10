#include <chrono>
#include <iostream>
#include <stdlib.h>  
#include <thread>

#include <lib/ADT_Stack.h>
#include <lib/Stack.cpp>
#include <lib/SimpleLockingStack.h>

using namespace std::chrono;

#define DEBUG false

#if DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#define OP_COUNT 100000
#define THREADS 4

int done_count = 0;
std::mutex done_mutex;
ADTOperationQueue * op_queue = new ADTOperationQueue();

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
    return operations;
}

void run_worker(Stack* stack) {
    std::vector<operation> operations = generate_operations_uniform();
    std::cout << "Worker: start" << std::endl;
    long op_counter = 0;
    for (operation op : operations) {
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
    done_mutex.lock();
    done_count ++;
    done_mutex.unlock();
    std::cout << "Worker: done" << std::endl;
}

void run_checker() {
    ADTStack * adt_stack = new ADTStack();
    while(true) {
        size_t queue_size = op_queue->size();
        
        if (done_count >= THREADS && queue_size == 0) {
            break;
        } else if(queue_size != 0){
            operation op = op_queue->dequeue();
            adt_stack->do_op(&op);
        }
    }
    std::cout << "Done checking operations" << std::endl;
}

int main(){
    Stack * s = new SimpleLockingStack(op_queue);

    std::thread *worker= new std::thread[THREADS];

    for (int i=0;i<THREADS;i++){
        worker[i]=std::thread(run_worker, s);		
    }

    std::thread monitor = std::thread(run_checker);

    for (int i=0;i<THREADS;i++){
        worker[i].join();	
    }

    monitor.join();	
    return 0;
}