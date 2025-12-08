#include <iostream>
#include <format>
#include <queue>
#include <cstddef>

int main()
{
    int N;
    std::cin >> N;
    std::queue<std::string> q;
    std::string op;
    std::string id;
    std::cin >> op;
    while (op != "#")
    {
        if (op == "Calling")
        {
            if (q.empty())
            {
                std::cout << "No one!\n";
            }
            else
            {
                id = q.front();
                q.pop();
                std::cout << std::format("{} called. Total:{}\n", id, q.size());
            }
        }
        else
        {
            std::cin >> id;
            if (q.size() == static_cast<std::size_t>(N))
            {
                std::cout << std::format("{} rejected.\n", id);
            }
            else
            {
                q.emplace(id);
                std::cout << std::format("{} joined. Total:{}\n", id, q.size());
            }
        }
        std::cin >> op;
    }
    return 0;
}