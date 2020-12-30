#include <mutex>

class Node { 
public: 
    int data; 
    bool is_dummy;
    Node* next;
    std::mutex mut; 
    public:
        Node(int element);
        static Node* Dummy();
        void lock();
        void unlock();
        bool is_smaller_than(int n);
        bool is_equal(int n);
};
Node::Node(int element){
    this->data = element;
    this->is_dummy = false;
}

Node* Node::Dummy(){
    Node* n = new Node(0);
    n->is_dummy = true;
    return n;
}

bool Node::is_smaller_than(int n) {
    // Everything is smaller than a dummy -> false
    return  this->data < n && !this->is_dummy;
}

bool Node::is_equal(int n) {
    // Dummies are not equal to any number -> false
    return  this->data == n && !this->is_dummy;
}

void Node::lock() {
    this->mut.lock();
} 
void Node::unlock() {
    this->mut.unlock();
}