#include <stack>
#include <vector>

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