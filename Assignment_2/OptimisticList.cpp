#pragma once

#include <bits/stdc++.h>

#include"Node.cpp"
#include"Set.cpp"

class OptimisticSet:public Set {
    protected:
        Node* first;
        bool validate(Node* p, Node* c);
    public:
        OptimisticSet();
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
        
};

OptimisticSet::OptimisticSet() : Set("OptimisticSet") { }

bool OptimisticSet::add(int element) {
    Node* p;
    Node* c;
    while (true) {
        p = this->first;
        c = p->next;
        while(c->is_smaller_than(element)) {
            p = c;
            c = c->next;
        }

        p->lock();
        c->lock();
        
        if(validate(p,c)) {
            if (c->is_equal(element)) {
                p->unlock();
                c->unlock();
                return false;
            } else {
                Node* n = new Node(element);
                n->next = c;
                p->next = n;
                p->unlock();
                c->unlock();
                return true;
            }
        } else {
            p->unlock();
            c->unlock();
        }
    }
}
bool OptimisticSet::rmv(int element) {
    Node* p;
    Node* c;
    while (true) {
        p = this->first;
        c = p->next;
        while(c->is_smaller_than(element)) {
            p = c;
            c = c->next;
        }

        p->lock();
        c->lock();
        
        if(validate(p,c)) {
            if (c->is_equal(element)) {
                p->next = c->next;

                p->unlock();
                c->unlock();
                return true;
            } else {
                p->unlock();
                c->unlock();
                return false;
            }
        } else {
            p->unlock();
            c->unlock();
        }
    }
}
bool OptimisticSet::ctn(int element) {
    Node* p;
    Node* c;
    while (true) {
        p = this->first;
        c = p->next;
        while(c->is_smaller_than(element)) {
            p = c;
            c = c->next;
        }

        p->lock();
        c->lock();
        
        if(validate(p,c)) {
            if (c->is_equal(element)) {
                p->unlock();
                c->unlock();
                return true;
            } else {
                p->unlock();
                c->unlock();
                return false;
            }
        } else {
            p->unlock();
            c->unlock();
        }
    }
}

bool OptimisticSet::validate(Node* p, Node* c) {
    Node* n = this->first;
    while (n->is_smaller_than(p)) {
        n = n->next;
    }
    if ((n == p) && (p->next == c)) {
        return true;
    } else {
        return false;
    }
}