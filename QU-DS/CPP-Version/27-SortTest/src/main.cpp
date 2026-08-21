#include "StudentTable.h"
#include <algorithm>
#include <cstddef>
#include <ios>
#include <iostream>
#include <print>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<StudentTable> v(n);
    for (std::size_t i = 0; i < n; ++i)
    {
        std::cin >> v[i].m_id >> v[i].m_name >> v[i].m_major >> v[i].m_class_num >> v[i].m_score;
    }
    std::sort(v.begin(),
              v.end(),
              [](const StudentTable& other1, const StudentTable& other2) -> bool
              {
                  if (other1.m_major != other2.m_major)
                  {
                      return other1.m_major < other2.m_major;
                  }
                  if (other1.m_class_num != other2.m_class_num)
                  {
                      return other1.m_class_num < other2.m_class_num;
                  }
                  return other1.m_score > other2.m_score;
              });
    std::println("学号\t姓名\t专业\t班级\t成绩");
    for (const auto& i : v)
    {
        std::println("{}", i);
    }
    return 0;
}