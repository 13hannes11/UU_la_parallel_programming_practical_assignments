#include <bits/stdc++.h>

#include"Node.cpp"

class LazySet {
    protected:
        Node* first;
        std::tuple<Node*, Node*> locate(int element);
    
    public:
        LazySet();
        bool add(int element);
        bool rmv(int element);
        bool ctn(int element);
};

LazySet::LazySet(){
    first = Node::Dummy(); // dummy node;
    Node* last = Node::Dummy();
    first->next = last;
}

bool LazySet::add(int element) {
    auto tuple = locate(element);
    Node* p = std::get<0>(tuple);
    Node* c = std::get<1>(tuple);

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
    auto tuple = locate(element);
    Node* p = std::get<0>(tuple);
    Node* c = std::get<1>(tuple);

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


std::tuple<Node*, Node*> LazySet::locate(int element) {
    Node* p = first;
    Node* c = p->next;

    while (c->is_smaller_than(element)) {
        p = c;
        c = c->next;
    }
    p->lock();
    c->lock();
    if (!p->deleted && !c->deleted && p->next == c) {
        p->unlock();
        c->unlock();
        return {p, c};
    }
    
    p->unlock();
    c->unlock();
    return {Node::Dummy(), Node::Dummy()};
}