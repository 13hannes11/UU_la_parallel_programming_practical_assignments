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

void benchmark(int minVal, int maxVal, benchmark_type b_type, int i){
    switch (b_type) {
        case benchmark_type::i:
            std::cout << "i distribution with i:" << i;
            break;
        default:
            std::cout << "uniform distribution";
            break;
    }
    std::cout << " (input range: ["<< minVal << "," << maxVal <<"])" << std::endl;

    std::vector<int> thread_counts{ 2, 4, 8, 16, 32, 64 };
    std::cout << "set\\threads";

    std::vector<Set*> sets{new FineSet(), new OptimisticSet(), new LazySet()};


    for (int thread_count : thread_counts) {
        std::cout << ";" << thread_count;
    }
    std::cout << std::endl;

    for (Set* set : sets) {
        std::cout << typeid(set).name();

        for (int thread_count : thread_counts) {
            
            benchmark_parameters params;
            params.type = b_type;
            params.minVal = minVal;
            params.maxVal = maxVal;
            params.i = i;
            params.duration_in_seconds = TEST_TIME_SECONDS;
            params.thread_count = thread_count;

            int count = benchmark_set(set, params);
            std::cout << ";" << count;
        }
        std::cout << std::endl;
    }
}

int main(){
    std::vector<int> max_counts{ 7, 1023};
    std::vector<int> i_values{10, 50, 90};

    for (int max : max_counts) {
        benchmark(0, max, benchmark_type::uniform, 0);
    }

    for (int i : i_values) {
        for (int max : max_counts) {
            benchmark(0, max, benchmark_type::i, i);
        }
    }

    return 0;
}