#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> array{111, 2, 3333, 4, 5};
    std::vector<int>::iterator it;
    for (it = array.begin(); it != array.end(); it++)
    {
        std::cout << *it << '\n';
    }
    it = std::find(array.begin(), array.end(), 3333);
    if (it != array.end())
    {
        std::cout << *it << '\n';
    }
    return 0;
}