#pragma once

#include <format>
#include <string>

struct StudentTable
{
        std::string m_major;
        int m_class_num;
        std::string m_name;
        int m_score;
        char m_id[5];
};

template <>
struct std::formatter<StudentTable, char>
{
        constexpr auto parse(std::format_parse_context& ctx)
        {
            return ctx.begin();
        }
        auto format(const StudentTable& st, std::format_context& ctx) const
        {
            return std::format_to(ctx.out(),
                                  "{}\t{}\t{}\t{}\t{}",
                                  st.m_id,
                                  st.m_name,
                                  st.m_major,
                                  st.m_class_num,
                                  st.m_score);
        }
};