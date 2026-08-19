#include <algorithm>
#include <array>
#include <print>

int main()
{
    std::array<int, 11> array({11, 222, 3, 44, 5, 666, -100, 0, 999, -123, 1});
    // std::sort(array.begin(), array.end());
    // std::sort(array.begin(), array.end(), std::greater<int>());
    std::sort(array.begin(),
              array.end(),
              [](int a, int b) -> bool
              {
                  return a > b;
              });
    for (const auto& i : array)
    {
        std::print("{} ", i);
    }
    std::println();
    return 0;
}