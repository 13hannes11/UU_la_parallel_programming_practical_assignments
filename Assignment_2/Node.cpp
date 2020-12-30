#include <mutex>

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