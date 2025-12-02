#include <iostream>
#include <string>
#include <format>
#include <regex>

int main()
{
    std::string str("abc123@abc12.xyz12");
    std::regex r("[a-z0-9]+@[a-z0-9]+\\.[a-z0-9]+");
    std::cout << std::format("{}\n", std::regex_match(str, r));
    return 0;
}