#include<iostream>
#include<set>
#include<stdexcept>
#include <sstream>
#include <stdlib.h>  

using namespace std;

enum methodname {add, rmv, ctn};
typedef struct _operation{
  //blah blah blah
  methodname method;
  int input;
  bool output;
} operation;

class ADT_Set {    
    std::set<int> set;
    public:
        ADT_Set();
        void do_op(operation *op);
        void add(int element, bool output);
        void rmv(int element, bool output);
        void ctn(int element, bool output);
};

ADT_Set::ADT_Set() {
    set = { };
}

void ADT_Set::do_op(operation *op) {
    switch (op->method) {
        case methodname::add:
            add(op->input, op->output);
            break;
        case methodname::rmv:
            rmv(op->input, op->output);
            break;
        case methodname::ctn:
            ctn(op->input, op->output);
            break;
        //default:
        //     throw invalid_argument("Uknown operation");
    }
}

void ADT_Set::add(int element, bool output){
    bool elem_in_set = set.find(element) != set.end();

    // Element in set -> output must be false
    // Element not in set - > output must be true 
    if(elem_in_set != output) {
        set.insert(element);
    } else {
        std::ostringstream oss;
        oss << std::boolalpha << "Invalid operation: add " << element << " " << output;
        throw invalid_argument(oss.str());
    }
}

void ADT_Set::rmv(int element, bool output){
    bool elem_in_set = set.find(element) != set.end();
    // Element in set -> output must be true
    // Element not in set - > output must be false 
    if(elem_in_set == output) {
        set.erase(element);
    } else {
        std::ostringstream oss;
        oss << std::boolalpha << "Invalid operation: rmv " << element << " " << output;
        throw invalid_argument(oss.str());
    }
}

void ADT_Set::ctn(int element, bool output){
    bool elem_in_set = set.find(element) != set.end();
    // Element in set -> output must be true
    // Element not in set - > output must be false 
    if(elem_in_set != output) {
        std::ostringstream oss;
        oss << std::boolalpha << "Invalid operation: ctn " << element << " " << output;
        throw invalid_argument(oss.str());
    }
}

operation create_random_operation() {
    methodname method;
    switch (rand() % 2) {
    case 0:
        method = methodname::add;
        break;
    case 1:
        method = methodname::rmv;
        break;
    default:
        method = methodname::ctn;
        break;
    }

    int element = rand() % 10;
    return {
        .method = method, .input = element, .output = NULL
    };
}

void fill_with_operations(operation * arr, int arr_size) {
    int arrSize = arr_size;
    for (int i = 0; i < arrSize; i++) {
        arr[i] = create_random_operation();
    }
}