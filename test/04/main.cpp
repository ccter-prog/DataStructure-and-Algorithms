#include "LinkedList.h"
#include <iostream>

int main()
{
    LinkedList<int> list;
    list.add(1);
    list.add(2);
    LinkedList<int>::iterator temp = list.begin();

    list.insert_after(temp++, 3);
    for (auto& i : list)
    {
        std::cout << i << '\n';
    }
    std::cout.put('\n');
    list.erase_after(temp);
    for (auto& i : list)
    {
        std::cout << i << '\n';
    }
    return 0;
}