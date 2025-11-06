#include "LinkedList.h"
#include <iostream>

int main()
{
    LinkedList<int> list;
    for (int i = 0; i < 10; )
    {
        list.add(i);
    }
    list.add(10);
    list.remove(0);
    for (auto& i : list)
    {
        std::cout << i << '\n';
    }
    return 0;
}