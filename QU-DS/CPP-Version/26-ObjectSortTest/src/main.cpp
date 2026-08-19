#include "Student.h"
#include <algorithm>
#include <print>
#include <vector>

int main()
{
    std::vector<Student> v;
    v.reserve(10);
    v.emplace_back("zhangsan", 95);
    v.emplace_back("lisi", 91);
    v.emplace_back("wangwu", 99);
    v.emplace_back("zhaoliu", 90);
    v.emplace_back("AAA", 96);

    std::sort(v.begin(),
              v.end(),
              [](const Student& stu1, const Student& stu2) -> bool
              {
                  return stu1 < stu2;
              });

    for (const auto& i : v)
    {
        std::println("{}", i);
    }
    return 0;
}