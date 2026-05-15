#include "DisjointSet.h"
// #include <gtest/gtest.h>
#include <iostream>
#include <string>

// TEST(DisjointSet, Find)
// {
//     DisjointSet<int> s(10);
//     s.insert(11);
//     s.insert(22);
//     s.insert(66);
//     s.insert(-5);
//     s.insert(123);
//     s.union_set(11, 22);
//     s.union_set(22, 66);
//     s.union_set(22, 123);
//     EXPECT_TRUE(s.connected(11, 22));
//     EXPECT_TRUE(s.connected(11, 66));
//     EXPECT_TRUE(s.connected(11, 123));
//     EXPECT_FALSE(s.connected(11, 123333));
//     EXPECT_TRUE(s.connected(11, 11));
//     EXPECT_TRUE(s.connected(11, 123));
// }
// int main(int argc, char** argv)
// {
//     testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }

int main()
{
    std::size_t M, N;
    std::cin >> N;
    DisjointSet<std::string> s(N);
    if (!s.status())
    {
        std::println("初始化失败");
    }
    std::string name, name2;
    for (std::size_t i = 0; i < N; ++i)
    {
        std::cin >> name;
        s.insert(name);
    }
    std::cin >> M;
    for (std::size_t i = 0; i < M; ++i)
    {
        std::cin >> name >> name2;
        s.union_set(name, name2);
    }
    s.print();
    return 0;
}