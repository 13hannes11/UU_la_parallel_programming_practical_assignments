#include <bits/stdc++.h>

#include"Node.h"
#include"Set.h"

class MultiSet:public Set {
    Node* first;
    public:
        MultiSet();
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
};

MultiSet::MultiSet() : Set("MultiSet") { }

bool MultiSet::add(int element) {
    this->first->lock();
    Node* p = this->first;
    Node* c = p->next;
    c->lock();
    while (c->is_smaller_than(element)) {
        p->unlock();
        p = c;
        c = c->next;
        c->lock();     
    }
    Node* n = new Node(element);
    n->next = c;
    p->next = n;
    
    c->unlock();
    p->unlock();
    return true; 
}

bool MultiSet::rmv(int element) {
    this->first->lock();
    Node* p = this->first;
    Node* c = p->next;
    c->lock();

    while (c->is_smaller_than(element)) {
        p->unlock();
        c = c->next;
        c->lock();        
    }

    if (c->is_equal(element)) {
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
bool MultiSet::ctn(int element) {
    this->first->lock();
    Node* p = this->first;
    Node* c = p->next;
    c->lock();

    while (c->is_smaller_than(element)) {
        p->unlock();
        c = c->next;
        c->lock();
    }

    if (c->is_equal(element)) {            
        c->unlock();
        p->unlock();
        return true;
    } else {
        c->unlock();
        p->unlock();
        return false;
    }
}