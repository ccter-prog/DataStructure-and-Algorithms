#include "HashTable.h"
#include <cstddef>
#include <optional>
#include <print>


int main()
{
    HashTable<int> h(11);
    h.insert(5);
    h.insert(16);
    h.insert(10);
    h.insert(21);
    std::optional<std::size_t> op(h.find(5));
    if (op.has_value())
    {
        std::println("{}", *op);
    }
    h.remove(5);
    h.print();
    return 0;
}