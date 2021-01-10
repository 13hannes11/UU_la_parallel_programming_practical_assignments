
#include <vector>
#include <mutex>

#include "Stack.h"

class SimpleLockingStack:public Stack{
    private:
        std::vector<int> vec;
        std::mutex mut;
    public:
        SimpleLockingStack(ADTOperationQueue * queue);
        void push(int element);
        int pop();
        int size();
};