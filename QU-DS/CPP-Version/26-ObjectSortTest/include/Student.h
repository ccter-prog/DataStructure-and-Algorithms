#pragma once

#include <format>
#include <string>

class Student
{
    public:
        // 特殊函数
        Student(const std::string& name, const int score);
    public:
        // 公共函数
        bool operator<(const Student& other) const;
        bool operator>(const Student& other) const;
    private:
        // 友元
        friend struct std::formatter<Student, char>;
    private:
        // 私有变量
        std::string m_name;
        int m_score;
};

inline Student::Student(const std::string& name, const int score) : m_name(name), m_score(score)
{
}

inline bool Student::operator<(const Student& other) const
{
    return m_score < other.m_score;
}

inline bool Student::operator>(const Student& other) const
{
    return m_score > other.m_score;
}

template <>
struct std::formatter<Student, char>
{
        constexpr auto parse(std::format_parse_context& ctx)
        {
            return ctx.begin();
        }
        auto format(const Student& stu, std::format_context& ctx) const
        {
            return std::format_to(ctx.out(), "[{}, {}]", stu.m_name, stu.m_score);
        }
};