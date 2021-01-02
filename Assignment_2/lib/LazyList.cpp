#include <bits/stdc++.h>

#include"Node.h"
#include"Set.h"

class LazySet:public Set {
    protected:
        void locate(int element, Node* prev, Node* cur);
    
    public:
        LazySet();
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
};

LazySet::LazySet() : Set("LazySet") { }

bool LazySet::add(int element) {
    Node* p;
    Node* c;
    locate(element, p, c);

    if (c->is_equal(element)) {
        p->unlock();
        c->unlock();
        return false;
    } else  {
        Node* n = new Node(element);
        p->next = n;

        p->unlock();
        c->unlock();
        return true;
    }
}
bool LazySet::rmv(int element) {
    Node* p;
    Node* c;
    locate(element, p, c);

    if (c->is_equal(element)) {
        c->deleted = true;
        p->next = c->next;

        p->unlock();
        c->unlock();
        return true;
    } else  {
        p->unlock();
        c->unlock();
        return false;
    }
}
bool LazySet::ctn(int element) {
    Node* c = first;
    while (c->is_smaller_than(element)) {
        c = c->next;
    }
    if (!c->is_equal(element) || c->deleted) {
        return false;
    } else {
        return true;
    }
}


void LazySet::locate(int element, Node* prev, Node* cur) {
    prev = Node::Dummy();
    cur = Node::Dummy();

    Node* p = first;
    Node* c = p->next;

    while (c->is_smaller_than(element)) {
        p = c;
        c = c->next;
    }
    p->lock();
    c->lock();
    if (!p->deleted && !c->deleted && p->next == c) {
        prev = p;
        cur = c;
    }
    
    p->unlock();
    c->unlock();
}