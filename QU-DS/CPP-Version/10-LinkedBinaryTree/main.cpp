#include "BinTree.h"
#include <string>

int main()
{
    std::string name;
    std::cin >> name;
    BinTree<std::string> bt(name);
    std::cin >> name;
    while (name != "-")
    {
        std::string lc, rc;
        std::cin >> lc >> rc;
        if (lc != "-")
        {
            bt.insert(name, 0, lc);
        }
        if (rc != "-")
        {
            bt.insert(name, 1, rc);
        }
        std::cin >> name;
    }
    std::println("Amount: {}", bt.count());
    return 0;
}