#pragma once

#include <cstdint>

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