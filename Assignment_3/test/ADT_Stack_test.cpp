#include <gtest/gtest.h>

#include <vector>
#include <stdexcept>
#include <lib/ADT_Stack.h>

TEST(ADTStackTest, SimplePushPop) {
    std::vector<operation> ops;

    ops.push_back(create_operation(methodname::push, 1));
    ops.push_back(create_operation(methodname::pop, 1));

    ADTStack * adt = new ADTStack();
    adt->do_ops(ops);
}

TEST(ADTStackTest, SimplePopWrong) {
    std::vector<operation> ops;
    ops.push_back(create_operation(methodname::push, 2));
    ops.push_back(create_operation(methodname::pop, 1));

    ADTStack * adt = new ADTStack();

    try {
        adt->do_ops(ops);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Invalid operation: pop 1 (actual top: 2)"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(ADTStackTest, PopEmpty) {
    std::vector<operation> ops;
    ops.push_back(create_operation(methodname::pop, 1));

    ADTStack * adt = new ADTStack();

    try {
        adt->do_ops(ops);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Invalid operation: pop 1 (stack is empty)"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST(ADTStackTest, SizeEmpty) {
    std::vector<operation> ops;
    ops.push_back(create_operation(methodname::size, 0));

    ADTStack * adt = new ADTStack();
    adt->do_ops(ops);
}
TEST(ADTStackTest, SizeEmptyWrong) {
    std::vector<operation> ops;
    ops.push_back(create_operation(methodname::size, 1));

    ADTStack * adt = new ADTStack();

    try {
        adt->do_ops(ops);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(),std::string("Invalid operation: size 1 (actual size: 0)"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

