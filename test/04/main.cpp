#include "LinkedList.h"

int main()
{
    LinkedList<int> list;
    for (int i = 1; i <= 10; i++)
    {
        list.add(i);
    }
    list.print();
    return 0;
}