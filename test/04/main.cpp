#include "LinkedList.h"
#include <iostream>

int main()
{
    LinkedList<int> list;
    for (int i = 0; i < 10; i++)
    {
        list.add(i);
    }
    LinkedList<int> temp;
    for (int i = 10; i < 20; i++)
    {
        temp.add(i);
    }
    LinkedList<int>::iterator it = list.begin();
    list.splice_after(it++, temp);
    for (auto& i : list)
    {
        std::cout << i << '\n';
    }
    return 0;
}