#include <gtest/gtest.h>

#include <lib/MultiSet.cpp>

TEST(MultiSetTest, add1_add1) {
    MultiSet * fl = new MultiSet();

    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->add(1));
}

TEST(MultiSetTest, add1_rmv1) {
    MultiSet * fl = new MultiSet();
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
}

TEST(MultiSetTest, rmv1) {
    MultiSet * fl = new MultiSet();
    ASSERT_FALSE(fl->rmv(1));
}

TEST(MultiSetTest, rmv1_add1_add1_rmv1_rmv1) {
    MultiSet * fl = new MultiSet();
    ASSERT_FALSE(fl->rmv(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_TRUE(fl->rmv(1));
}

TEST(MultiSetTest, rmv1_add1_rmv1_rmv1) {
    MultiSet * fl = new MultiSet();
    ASSERT_FALSE(fl->rmv(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->rmv(1));
}

TEST(MultiSetTest, ctn1) {
    MultiSet * fl = new MultiSet();
    ASSERT_FALSE(fl->ctn(1));
}

TEST(MultiSetTest, ctn1_add1_ctn1) {
    MultiSet * fl = new MultiSet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));;
}

TEST(MultiSetTest, ctn1_add1_ctn1_rmv1_ctn1) {
    MultiSet * fl = new MultiSet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->ctn(1));
}