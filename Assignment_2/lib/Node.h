#pragma once

#include <mutex>

class Node { 
    protected:
        int data; 
        bool is_dummy;
        std::mutex mut;

    public:
        Node* next;
        bool deleted;

        Node(int element);
        static Node* Dummy();
        //  Dummy();

        void lock();
        void unlock();
        bool is_smaller_than(int n);
        bool is_smaller_than(Node* n);
        bool is_equal(int n);
};