// #include "LinkedQueue.h"
#include <iostream>
#include <format>
#include <queue>

int main()
{
    std::queue<int> q;
    q.push(11);
    q.push(22);
    int x = q.front();
    std::cout << std::format("{}\n", x);
    q.pop();
    x = q.front();
    std::cout << std::format("{}\n", x);

    // LinkedQueue<int> lq;
    // int temp;
    // for (int i = 1; i <= 6; i++)
    // {
    //     lq.enQueue(i);
    //     lq.Front(temp);
    //     std::cout << std::format("{}\n", temp);
    //     lq.deQueue();
    // }
    return 0;
}