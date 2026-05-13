#include "DisjointSet.h"
#include <gtest/gtest.h>

TEST(DisjointSet, Find)
{
    DisjointSet<int> s(10);
    s.insert(11);
    s.insert(22);
    s.insert(66);
    s.insert(-5);
    s.insert(123);
    s.union_set(11, 22);
    EXPECT_TRUE(s.connected(11, 22));
}
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
