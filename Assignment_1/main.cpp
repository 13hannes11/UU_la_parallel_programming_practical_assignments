#include"adt_set.cpp"
#include"set.cpp"
#include"concurrent_set.cpp"

#define TEST_CASE_COUNT 1000

enum program {adt_set, test_one_set, one_thread_set, n_thread_set, concurrent_set};

int run_adt_set(){
    ADT_Set adt_set = ADT_Set(); 
    operation test_case[6] = {
        { methodname::add, 1, true },
        { methodname::add, 1, false },
        { methodname::ctn, 1, true },
        { methodname::rmv, 1, true },
        { methodname::ctn, 1, false },
        { methodname::rmv, 1, false }
    };

    for (operation op : test_case) {
        adt_set.do_op(&op);
    }
    return 0;
}

int run_N_thread_set(int N) {
    int worker_count = N;
    thread *worker= new thread[worker_count];
    operation test_case[TEST_CASE_COUNT];

    fill_with_operations(test_case, TEST_CASE_COUNT);

    thread monitor = thread(monitor_func,test_case, worker_count);

    for (int i=0;i<worker_count;i++){
        worker[i]=thread(worker_func, i, test_case, TEST_CASE_COUNT, worker_count);		
    }

    for (int i=0;i<worker_count;i++){
        worker[i].join();	
    }

    monitor.join();	
    return 0;
}

int run_one_thread_set() {
    return run_N_thread_set(1);
}

int run_N_thread_concurrent_set(int N) {
    int worker_count = N;
    thread *worker= new thread[worker_count];
    operation test_case[TEST_CASE_COUNT];

    fill_with_operations(test_case, TEST_CASE_COUNT);

    thread monitor = thread(monitor_func, test_case, worker_count);

    for (int i=0;i<worker_count;i++){
        worker[i]=thread(conc_worker_func, i, test_case, TEST_CASE_COUNT, worker_count);		
    }

    for (int i=0;i<worker_count;i++){
        worker[i].join();	
    }

    monitor.join();	
    return 0;
}


int main(){
    program p = program::concurrent_set; // change this

    switch (p) {
        case program::adt_set:
            return run_adt_set();
            break;
        case program::one_thread_set:
            return run_one_thread_set();
            break; 
        case program::n_thread_set:
            return run_N_thread_set(4);
            break;
        case program::test_one_set:
            return test_set();
            break;    
        case program::concurrent_set:
            return run_N_thread_concurrent_set(2);
            break;    
    }

}