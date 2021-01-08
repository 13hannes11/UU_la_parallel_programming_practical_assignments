#include <chrono>
#include <iostream>
#include <stdlib.h>  

#include <lib/Set.cpp>

using namespace std::chrono;

#define DEBUG false

#if DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#define OP_COUNT 100000

enum methodname {add, rmv, ctn, noop};
typedef struct _operation{
  methodname method;
  int input;
} operation;

void do_operation(operation* op, Set* set) {
    switch (op->method) {
        case methodname::ctn:
            set->ctn(op->input);
            break;
        case methodname::add:
            set->add(op->input);
            break;
        case methodname::rmv:
            set->rmv(op->input);
            break;
        default:
            break;
    }
};

//void generate_operations_uniform(std::vector<operation> *operations, int minVal, int maxVal) {
//    int range_size = maxVal - minVal;
//    for (auto op = operations->begin(); op != operations->end(); op++) {
//        op->input = (rand() % range_size) + minVal;
//        switch (rand() % 3) {
//            case 0:
//                op->method = methodname::add;
//                break;
//            case 1:
//                op->method = methodname::rmv;
//                break;
//            default:
//                op->method = methodname::ctn;
//                break;
//        }
//    }
//}

//void generate_operations(std::vector<operation> *operations, int minVal, int maxVal, int i) {
//    int range_size = maxVal - minVal;
//    for (auto op = operations->begin(); op != operations->end(); op++) {
//        op->input = (rand() % range_size) + minVal;

//        if (rand() % 100 < i) {
//            op->method = methodname::ctn;
//        } else if (rand() % 10 < 9) {
//            op->method = methodname::add;            
//        } else {
//            op->method = methodname::rmv;
//        }
//    }
//    DEBUG_MSG("Generated operations with i = "<< i);
//}

//void run_worker(std::vector<operation>* operations, Set* set) {    
//    DEBUG_MSG("Run worker");
//    long op_counter = 0;
//    for (operation op : operations) {
        /* code */
//        do_operation(&op, set);
//    }
//}

int main(){
    return 0;
}