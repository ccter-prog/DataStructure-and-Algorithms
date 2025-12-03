#include <iostream>
#include <format>
#include <list>

int main()
{
    std::list<int> a;
    a.push_back(11);
    a.push_back(22);
    a.push_back(33);
    a.insert(a.begin(), 666);
    for (auto& i : a)
    {
        std::cout << std::format("{},", i);
    }
    std::cout.put('\n');
    return 0;   
}