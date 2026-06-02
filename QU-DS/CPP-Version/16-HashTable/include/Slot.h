#pragma once

#include <cstdint>
#include <format>

enum class GridStatus : std::uint8_t
{
    Empty,
    Active,
    Delete
};

template <typename T>
struct Slot
{
        Slot();
        T value;
        GridStatus status;
};

template <typename T>
inline Slot<T>::Slot() : status(GridStatus::Empty)
{
}

template <typename T>
struct std::formatter<Slot<T>>
{
        constexpr auto parse(std::format_parse_context& ctx)
        {
            return ctx.begin();
        }

        auto format(const Slot<T>& slot, std::format_context& ctx) const
        {
            switch (slot.status)
            {
                case GridStatus::Active:
                    return std::format_to(ctx.out(), "{} - [Active]", slot.value);
                case GridStatus::Delete:
                    return std::format_to(ctx.out(), "{} - [Delete]", slot.value);
                default:
                    return std::format_to(ctx.out(), "[Empty]");
            }
        }
};