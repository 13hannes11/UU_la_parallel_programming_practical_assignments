#include <gtest/gtest.h>

#include <lib/TreiberStack.h>


TEST(TreiberStackTest, SimpleEmptyPrint) {
    TreiberStack * stack = new TreiberStack(new ADTOperationQueue());
    EXPECT_EQ("", stack->print_stack());
}