#include <iostream>
#include <format>
#include <stack>

int main()
{
    std::stack<int> st;
    st.push(11);
    st.push(22);
    std::cout << std::format("size = {}\n", st.size());
    return 0;
}