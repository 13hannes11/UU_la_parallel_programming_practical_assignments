#ifndef ADT_Stack_H
#define ADT_Stack_H

#include <stack>
#include <vector>
#include <mutex>
#include <queue>

enum methodname {push, pop, size, noop};
typedef struct _operation{
  methodname method;
  int value;
} operation;

operation create_operation(methodname name, int value);

class ADTStack {
    private:
        std::stack<int> stack;
    public:
        void push(int element);
        void pop(int output);
        void size(int output);
        void do_op(operation * op);
        void do_ops(std::vector<operation> ops);
};

class ADTOperationQueue{
  private:
    std::queue<operation> queue;
    std::mutex mutex;
  public:
    void enqueue(operation op);
    operation dequeue();
    size_t size();
};

#endif