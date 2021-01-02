#include <gtest/gtest.h>

#include <lib/FineList.cpp>


TEST(FineSetTest, add1_add1) {
    FineSet * fl = new FineSet();

    ASSERT_TRUE(fl->add(1));
    ASSERT_FALSE(fl->add(1));
}

    FineSet * fl = new FineSet();
    //ASSERT_TRUE(fl->add(1));
}
