#include "shell_sort.h"
#include <print>
#include <array>

int main()
{
    std::array<int, 5> arr({5, 2, 4, 6, 1});
    shell_sort::print(arr);
    std::println("-----------------");
    shell_sort::shell_sort(arr);
    shell_sort::print(arr);
	return 0;
}