#include <gtest/gtest.h>

#include <lib/LazyList.cpp>



TEST(LazySetTest, add1_add1) {
    LazySet * fl = new LazySet();

    ASSERT_TRUE(fl->add(1));
    ASSERT_FALSE(fl->add(1));
}

TEST(LazySetTest, add1_rmv1) {
    LazySet * fl = new LazySet();
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
}

TEST(LazySetTest, rmv1) {
    LazySet * fl = new LazySet();
    ASSERT_FALSE(fl->rmv(1));
}

TEST(LazySetTest, rmv1_add1_rmv1_rmv1) {
    LazySet * fl = new LazySet();
    ASSERT_FALSE(fl->rmv(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->rmv(1));
}

TEST(LazySetTest, ctn1) {
    LazySet * fl = new LazySet();
    ASSERT_FALSE(fl->ctn(1));
}

TEST(LazySetTest, ctn1_add1_ctn1) {
    LazySet * fl = new LazySet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));;
}

TEST(LazySetTest, ctn1_add1_ctn1_rmv1_ctn1) {
    LazySet * fl = new LazySet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->ctn(1));
}
