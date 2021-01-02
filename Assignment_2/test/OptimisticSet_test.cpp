#include <gtest/gtest.h>

#include <lib/OptimisticList.cpp>

TEST(OptimisticSetTest, add1_add1) {
    OptimisticSet * fl = new OptimisticSet();

    ASSERT_TRUE(fl->add(1));
    ASSERT_FALSE(fl->add(1));
}

TEST(OptimisticSetTest, add1_add2) {
    OptimisticSet * fl = new OptimisticSet();

    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->add(2));
}

TEST(OptimisticSetTest, add1_rmv1) {
    OptimisticSet * fl = new OptimisticSet();
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
}

TEST(OptimisticSetTest, rmv1) {
    OptimisticSet * fl = new OptimisticSet();
    ASSERT_FALSE(fl->rmv(1));
}

TEST(OptimisticSetTest, rmv1_add1_rmv1_rmv1) {
    OptimisticSet * fl = new OptimisticSet();
    ASSERT_FALSE(fl->rmv(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->rmv(1));
}

TEST(OptimisticSetTest, ctn1) {
    OptimisticSet * fl = new OptimisticSet();
    ASSERT_FALSE(fl->ctn(1));
}

TEST(OptimisticSetTest, ctn1_add1_ctn1) {
    OptimisticSet * fl = new OptimisticSet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));;
}

TEST(OptimisticSetTest, ctn1_add1_ctn1_rmv1_ctn1) {
    OptimisticSet * fl = new OptimisticSet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->ctn(1));
}
