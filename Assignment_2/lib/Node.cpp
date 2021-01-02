#include <mutex>
#include <lib/Node.h>

Node::Node(int element){
    data = element;
    dummy = false;
    deleted = false;
}

Node* Node::Dummy(){
    Node* n = new Node(0);
    n->dummy = true;
    return n;
}

bool Node::is_smaller_than(Node* n) {
    return this->is_smaller_than(n->data);
}

bool Node::is_smaller_than(int n) {
    // Everything is smaller than a dummy -> false
    return  this->data < n && !this->dummy;
}

bool Node::is_equal(int n) {
    // Dummies are not equal to any number -> false
    return  this->data == n && !this->dummy;
}

void Node::lock() {
    this->mut.lock();
} 
void Node::unlock() {
    this->mut.unlock();
}

bool Node::is_dummy() {
    return dummy;
}

int Node::get_data(){
    return data;
}