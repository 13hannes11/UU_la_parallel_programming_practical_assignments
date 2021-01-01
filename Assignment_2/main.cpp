#include <chrono>
#include <iostream>
#include <stdlib.h>  

#include "Set.cpp"
#include "LazyList.cpp"
#include "FineList.cpp"
#include "OptimisticList.cpp"

using namespace std::chrono;

#define DEBUG false

#if DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#define TEST_TIME_SECONDS 10
#define OP_COUNT 100000

enum methodname {add, rmv, ctn, noop};
typedef struct _operation{
  methodname method;
  int input;
} operation;

enum benchmark_type {uniform, i};
typedef struct _benchmark_parameters{
  benchmark_type type;
  int i;
  int maxVal;
  int minVal;
  int duration_in_seconds; 
  int thread_count;
} benchmark_parameters;

typedef struct _benchmark_result{
    long count;
    std::mutex mutex;
} benchmark_result;

void add_worker_result(benchmark_result * result, int value){
    result->mutex.lock();
    result->count += value;
    result->mutex.unlock();
}

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

void generate_operations_uniform(std::vector<operation> *operations, int minVal, int maxVal) {
    int range_size = maxVal - minVal;
    for (auto op = operations->begin(); op != operations->end(); op++) {
        op->input = (rand() % range_size) + minVal;
        switch (rand() % 3) {
            case 0:
                op->method = methodname::add;
                break;
            case 1:
                op->method = methodname::rmv;
                break;
            default:
                op->method = methodname::ctn;
                break;
        }
    }
}

void generate_operations(std::vector<operation> *operations, int minVal, int maxVal, int i) {
    int range_size = maxVal - minVal;
    for (auto op = operations->begin(); op != operations->end(); op++) {
        op->input = (rand() % range_size) + minVal;

        if (rand() % 100 < i) {
            op->method = methodname::ctn;
        } else if (rand() % 10 < 9) {
            op->method = methodname::add;            
        } else {
            op->method = methodname::rmv;
        }
    }
    DEBUG_MSG("Generated operations with i = "<< i);
}

std::chrono::duration<int64_t, std::nano> time_delta(high_resolution_clock::time_point first, high_resolution_clock::time_point second) {
    if(first > second) {
        return first - second;
    } else {
        return second - first;
    }
}

void run_worker(benchmark_result * result, std::vector<operation>* operations, Set* set,high_resolution_clock::time_point start_time, int duration_in_seconds) {
    std::vector<operation>::iterator i = operations->begin();
    
    DEBUG_MSG("Run worker");
    long op_counter = 0;
    while (time_delta(start_time, high_resolution_clock::now()) < std::chrono::seconds(duration_in_seconds)) {
        
        do_operation(& *i, set);
        op_counter++;

        if(i == operations->end()) {
            i = operations->begin();
        } else {
            i++;
        }
    }
    DEBUG_MSG("Op Counter: "<<op_counter);
    add_worker_result(result, op_counter);
}

int benchmark_set(Set *set, benchmark_parameters param) {
    operation noop;
    noop.method = methodname::noop;
    std::vector<operation> operations(OP_COUNT, noop);

    

    switch (param.type) {
        case benchmark_type::uniform:
            generate_operations_uniform(&operations, param.minVal, param.maxVal);
            break;
        case benchmark_type::i:
            generate_operations(&operations, param.minVal, param.maxVal, param.i);
            break;
    }

    std::vector<std::thread> workers(param.thread_count);
   
    benchmark_result result;
    result.count = 0;

    DEBUG_MSG("About to start benchmark");
    high_resolution_clock::time_point start_time = high_resolution_clock::now();

    for (auto & worker : workers) {
        worker = std::thread(run_worker, &result, &operations, set, start_time, param.duration_in_seconds);
    }

    for (std::thread & worker : workers) {
        worker.join();
    }

    return result.count; 
}

int main(){
    Set * fineSet = new FineSet();

    benchmark_parameters params;
    params.type = benchmark_type::uniform;
    params.minVal = 0;
    params.maxVal = 7;
    params.duration_in_seconds = 10;
    params.thread_count = 2;

    int count = benchmark_set(fineSet, params);

    std::cout<<"Throughput in 10s: "<< count <<std::endl;
    return 0;
}