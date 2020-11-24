#pragma once

#include <mutex>
#include"set.cpp"
#include"adt_set.cpp"

class ConcurrentSet {
    Set cset;
    std::mutex cmut;

    public:
        ConcurrentSet();
        bool do_op(methodname method, int input);
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
};
ConcurrentSet::ConcurrentSet(){
    cset = Set();
}

bool ConcurrentSet::do_op(methodname method, int input){
    switch (method) {
        case methodname::add:
            return add(input);
        case methodname::rmv:
            return rmv(input);
            break;
        case methodname::ctn:
            return ctn(input);
        default:
             throw std::invalid_argument("Uknown operation");
    }
}

bool ConcurrentSet::add(int element) {
    bool res;
    cmut.lock();
    res = cset.add(element);
    cmut.unlock();
    return res;
}
bool ConcurrentSet::rmv(int element) {
    bool res;
    cmut.lock();
    res = cset.rmv(element);
    cmut.unlock();
    return res;
}
bool ConcurrentSet::ctn(int element) {
    bool res;
    cmut.lock();
    res = cset.ctn(element);
    cmut.unlock();
    return res;
}

void conc_worker_func(int num, operation * test_case, int test_case_count, int worker_count){//note that arrays are passed as pointers
    int arrSize = test_case_count;
    for (int i = 0; i < arrSize; i++) {
        q_mutex.lock();
        bool output = worker_set.do_op(test_case[i].method, test_case[i].input);
        done_queue.push({ .method = test_case[i].method, .input = test_case[i].input, .output = output});
        q_mutex.unlock();
    }
    q_mutex.lock();
    done_count += 1;
    cout<<"Worker "<<num<<endl;
    q_mutex.unlock();
}

int test_concurrent_set() {
    ConcurrentSet* s = new ConcurrentSet;
    assert(!s->rmv(1));
    assert(!s->ctn(1));
    assert(s->add(1));
    assert(!s->add(1));
    assert(s->ctn(1));
    assert(s->rmv(1));
    assert(!s->ctn(1));
    return 1;
}