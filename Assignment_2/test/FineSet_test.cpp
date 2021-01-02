#include <gtest/gtest.h>

#include <lib/FineList.cpp>


TEST(FineSetTest, add1_add1) {
    FineSet * fl = new FineSet();

    ASSERT_TRUE(fl->add(1));
    ASSERT_FALSE(fl->add(1));
}

TEST(FineSetTest, add1_add2) {
    FineSet * fl = new FineSet();

    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->add(2));
}

TEST(FineSetTest, add1_rmv1) {
    FineSet * fl = new FineSet();
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
}

TEST(FineSetTest, rmv1) {
    FineSet * fl = new FineSet();
    ASSERT_FALSE(fl->rmv(1));
}

TEST(FineSetTest, rmv1_add1_rmv1_rmv1) {
    FineSet * fl = new FineSet();
    ASSERT_FALSE(fl->rmv(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->rmv(1));
}

TEST(FineSetTest, ctn1) {
    FineSet * fl = new FineSet();
    ASSERT_FALSE(fl->ctn(1));
}

TEST(FineSetTest, ctn1_add1_ctn1) {
    FineSet * fl = new FineSet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));;
}

TEST(FineSetTest, ctn1_add1_ctn1_rmv1_ctn1) {
    FineSet * fl = new FineSet();
    ASSERT_FALSE(fl->ctn(1));
    ASSERT_TRUE(fl->add(1));
    ASSERT_TRUE(fl->ctn(1));
    ASSERT_TRUE(fl->rmv(1));
    ASSERT_FALSE(fl->ctn(1));
}
