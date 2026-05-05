#include <print>
#include <set>


int main()
{
    std::set<int> s({123, 23, 11, -5, 666});
    std::set<int> s2({11, 99});
    s.insert(s2.begin(), s2.end());
    for (const auto i : s)
    {
        std::println("{}", i);
    }
    return 0;
}