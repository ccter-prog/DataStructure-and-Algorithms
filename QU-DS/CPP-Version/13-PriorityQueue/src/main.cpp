#include <print>
#include <queue>
#include <vector>
#include <functional>

int main()
{
    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    q.push(111);
    q.push(222);
    q.push(333);
    q.push(11);
    q.push(22);
    std::println("{}", q.top());
    q.pop();
    std::println("{}", q.top());
    q.pop();
    return 0;
}