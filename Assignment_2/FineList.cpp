#include<iostream>
#include<thread>
#include <algorithm>
#include <queue>
#include <mutex>
#include <assert.h>
#include <bits/stdc++.h> 

// TODO: implement fine grained locking

class Node { 
public: 
    int data; 
    Node* next;
    std::mutex mut; 
    public:
        void lock();
        void unlock();
};
void Node::lock() {
    this->mut.lock();
} 
void Node::unlock() {
    this->mut.unlock();
}

class Set {
    Node* first;
    public:
        Set();
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
};

Set::Set(){
    first = new Node(); // dummy node;
    Node* last = new Node();
    last->data = INT_MAX; // end node;
    first->next = last;
}

bool Set::add(int element) {
    this->first->lock();
    Node* p = this->first;
    Node* c = p->next;
    c->lock();
    while (c->data < element) {
        p->unlock();
        p = c;
        c = c->next;
        c->lock();     
    }

    if (c->data == element) {
        c->unlock();
        p->unlock();
        return false;
    }  else {
        Node* n = new Node();
        n->data = element;
        n->next = c;
        p->next = n;
        
        c->unlock();
        p->unlock();
        return true; 
    }
}

bool Set::rmv(int element) {
    this->first->lock();
    Node* p = this->first;
    Node* c = p->next;
    c->lock();

    while (c->data < element) {
        p->unlock();
        c = c->next;
        c->lock();        
    }

    if (c->data == element) {
        p->next = c->next;

        c->unlock();
        p->unlock();
        return true;
    } else {
        c->unlock();
        p->unlock();
        return false;
    }
}
bool Set::ctn(int element) {
    this->first->lock();
    Node* p = this->first;
    Node* c = p->next;
    c->lock();

    while (c->data < element) {
        p->unlock();
        c = c->next;
        c->lock();
    }

    if (c->data == element) {            
        c->unlock();
        p->unlock();
        return true;
    } else {
        c->unlock();
        p->unlock();
        return false;
    }
}