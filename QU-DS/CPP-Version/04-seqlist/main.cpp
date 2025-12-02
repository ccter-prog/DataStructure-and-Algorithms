#include <iostream>
#include <format>
#include <vector>

int main()
{
    std::vector<int> v;
    v.push_back(11);
    v.push_back(22);
    v.push_back(33);
    v.insert(v.begin() + 2, 666);
    v.erase(v.begin() + 1);
    for (auto i : v)
    {
        std::cout << std::format("{} ", i);
    }
    std::cout.put('\n');
    return 0;
}