#pragma once

#include<iostream>
#include<thread>
#include <algorithm>
#include <queue>
#include <mutex>
#include <assert.h>  
#include"adt_set.cpp"


class Node { 
public: 
    int data; 
    Node* next; 
}; 


class Set {
    Node* first;
    public:
        Set();
        bool do_op(methodname method, int input);
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
};

Set::Set(){
    first = new Node(); // dummy node;
}

bool Set::do_op(methodname method, int input){
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

bool Set::add(int element) {
    bool element_in_list = ctn(element);
    if (!element_in_list) {
        Node* tmp = new Node();
        tmp->data = element;
        tmp->next = first->next;
        first->next = tmp;
        return true;
    } else {
        return false;
    }
}
bool Set::rmv(int element) {
    Node* current = first;
    Node* prev = first;
    while(current != NULL) {
        prev = current;
        current = current->next;
        if (current != NULL && current->data == element) {
            prev->next = current->next;
            return true;
        }
    }
    return false;
}
bool Set::ctn(int element) {
    Node* current = first;
    while(current != NULL) {
        current = current->next;
        if (current != NULL && current->data == element) {
            return true;
        }
    }
    return false;
}

std::mutex q_mutex;
std::queue<operation> done_queue = queue<operation>();
int done_count = 0;

Set worker_set = Set();

void worker_func(int num, operation * test_case, int test_case_count, int worker_count){//note that arrays are passed as pointers
    int arrSize = test_case_count;
    for (int i = 0; i < arrSize; i++) {
        bool output = worker_set.do_op(test_case[i].method, test_case[i].input);
        q_mutex.lock();
        done_queue.push({ .method = test_case[i].method, .input = test_case[i].input, .output = output});
        q_mutex.unlock();
    }
    q_mutex.lock();
    done_count += 1;
    cout<<"Worker "<<num<<endl;
    q_mutex.unlock();
}

void monitor_func(operation test_case[], int worker_count){
    ADT_Set adt_set = ADT_Set();
    //blah blah blah
    bool done = false;
    while (!done) {
        q_mutex.lock();
        if(done_count == worker_count && done_queue.empty()) {
            done = true;
        } else if(!done_queue.empty()) {
            operation op = done_queue.front();
            done_queue.pop();
            adt_set.do_op(&op);
        }
        q_mutex.unlock();
    }
    cout<<"Monitor"<<endl;
}

int test_set() {
    Set s = Set();
    assert(!s.rmv(1));
    assert(!s.ctn(1));
    assert(s.add(1));
    assert(!s.add(1));
    assert(s.ctn(1));
    assert(s.rmv(1));
    assert(!s.ctn(1));
    return 1;
}