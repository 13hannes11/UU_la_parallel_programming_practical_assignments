#include <atomic>

#include "Stack.h"
#include "Node.h"

class TreiberStack:public Stack{
    private:
        std::atomic<int> count;
        std::atomic<Node *> top;
    public:
        TreiberStack(ADTOperationQueue * queue);
        void push(int element);
        int pop();
        int size();
};