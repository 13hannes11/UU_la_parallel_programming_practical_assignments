#include <chrono>
#include <iostream>
#include <stdlib.h>  

#include "Set.cpp"
#include "LazyList.cpp"
#include "FineList.cpp"
#include "OptimisticList.cpp"

using namespace std::chrono;


#define TEST_TIME_SECONDS 10
#define OP_COUNT 1000

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
} benchmark_parameters;

typedef struct _benchmark_result{
    int count;
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
}

int time_delta(high_resolution_clock::time_point first, high_resolution_clock::time_point second) {
    return abs((first - second).count());
}

void run_worker(benchmark_result * result, std::vector<operation>* operations, Set* set,high_resolution_clock::time_point start_time, int duration_in_seconds) {
    std::vector<operation>::iterator i = operations->begin();
    int op_counter = 0;
    while (time_delta(start_time, high_resolution_clock::now()) < duration_in_seconds * 1000) {
        do_operation(& *i, set);
        op_counter++;

        if(i == operations->end()) {
            break;
        }
        i++;
    }
    add_worker_result(result, op_counter);
}

int benchmark_set(Set *set, int duration_in_seconds, int thread_count, benchmark_parameters param) {
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

    std::vector<std::thread> workers(thread_count);
   
    benchmark_result result;
    result.count = 0;

    high_resolution_clock::time_point start_time = high_resolution_clock::now();

    for (auto & worker : workers) {
        std::thread(run_worker, &result, &operations, set, start_time, TEST_TIME_SECONDS);
    }

    for (auto & worker : workers) {
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

    int count = benchmark_set(fineSet, 10, 4, params);

    std::cout<<"Throughput in 10s: "<< count <<std::endl;
    return 0;
}