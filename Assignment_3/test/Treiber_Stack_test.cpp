#include <gtest/gtest.h>

#include <lib/TreiberStack.h>
#include <iostream>


TEST(TreiberStackTest, EmptyPrint) {
    TreiberStack * stack = new TreiberStack(new ADTOperationQueue());
    EXPECT_EQ("", stack->print_stack());
}

TEST(TreiberStackTest, Push) {
    TreiberStack * stack = new TreiberStack(new ADTOperationQueue());
    stack->push(1);
    EXPECT_EQ("1", stack->print_stack());
}

TEST(TreiberStackTest, PushPop) {
    TreiberStack * stack = new TreiberStack(new ADTOperationQueue());
    stack->push(1);
    EXPECT_EQ(1, stack->pop());
    EXPECT_EQ("", stack->print_stack());
}

TEST(TreiberStackTest, SizeZero) {
    TreiberStack * stack = new TreiberStack(new ADTOperationQueue());
    EXPECT_EQ(0, stack->size());
}

TEST(TreiberStackTest, SizeAfterPush) {
    TreiberStack * stack = new TreiberStack(new ADTOperationQueue());
    stack->push(1);
    EXPECT_EQ(1, stack->size());
}

TEST(TreiberStackTest, SizeAfterPushPop) {
    TreiberStack * stack = new TreiberStack(new ADTOperationQueue());
    stack->push(1);
    stack->pop();
    EXPECT_EQ(0, stack->size());
}