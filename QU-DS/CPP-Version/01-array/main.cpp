#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int> obj)
{
    for (auto i : obj)
    {
        os << i << ' ';
    }
    return os;
}

int main()
{
    std::vector<int> array {1, 2, 3, 4, 5};
    std::cout << array[1] << '\n';
    std::cout << array << '\n';
    return 0;
}