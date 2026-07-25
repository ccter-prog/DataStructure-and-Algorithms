#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <queue>
#include <vector>

// 场景为：有11名学生上课，学生学号范围为1-999号

namespace RadixSort
{
    // 声明
    template <std::size_t N>
    inline void radix_sort(std::array<int, N>& array);

    inline void move_value_to_first(std::vector<int>& vec,
                                    const std::size_t delete_count,
                                    const std::size_t valid_count);

    // 定义
    template <std::size_t N>
    inline void radix_sort(std::array<int, N>& array)
    {
        if constexpr (N < 2)
        {
            return;
        }
        auto max_value = *std::max_element(array.begin(), array.end());
        std::size_t remaining_digits = 0;
        while (max_value != 0)
        {
            max_value /= 10;
            ++remaining_digits;
        }
        // std::array<std::queue<int>, 10> temp_array;
        std::array<std::vector<int>, 10> temp_array;
        for (const auto& j : array)
        {
            std::size_t index = static_cast<std::size_t>(j % 10);
            // temp_array[index].push(j);
            temp_array[index].push_back(j);
        }
        --remaining_digits;

        int divisort = 10;
        std::array<std::size_t, 10> vector_delete({0});

        while (remaining_digits > 0)
        {
            std::array<std::size_t, 10> vector_size;
            for (std::size_t i = 0; i < 10; ++i)
            {
                vector_size[i] = temp_array[i].size() - vector_delete[i];
                if (vector_delete[i] > vector_size[i])
                {
                    move_value_to_first(temp_array[i], vector_delete[i], vector_size[i]);
                    vector_delete[i] = 0;
                }
            }
            for (std::size_t i = 0; i < 10; ++i)
            {
                // std::size_t queue_size = temp_array[i].size();
                // while (queue_size > 0)
                std::size_t vector_read_index = vector_delete[i];
                while (vector_size[i] > 0)
                {
                    int temp_value = temp_array[i][vector_read_index];
                    ++vector_read_index, ++vector_delete[i];
                    // temp_array[i].pop();
                    --vector_size[i];
                    std::size_t index = static_cast<std::size_t>(temp_value / divisort % 10);
                    // temp_array[index].push(temp_value);
                    temp_array[index].push_back(temp_value);
                }
            }
            --remaining_digits;
            divisort *= 10;
        }
        // for (std::size_t i = 0; i < 10; ++i)
        //{
        //     std::size_t queue_size = temp_array[i].size();
        //     while (queue_size > 0)
        //     {
        //         int temp_value = temp_array[i].front();
        //         temp_array[i].pop();
        //         --queue_size;
        //         std::size_t index = static_cast<std::size_t>(temp_value / 100 % 10);
        //         temp_array[index].push(temp_value);
        //     }
        // }
        std::size_t list = 0;
        for (std::size_t i = 0; i < 10; ++i)
        {
            // while (!temp_array[i].empty())
            //{
            //     array[list++] = temp_array[i].front();
            //     temp_array[i].pop();
            // }

            std::size_t vector_size = temp_array[i].size() - vector_delete[i];
            std::size_t vector_read_index = vector_delete[i];
            while (vector_size > 0)
            {
                array[list++] = temp_array[i][vector_read_index++];
                --vector_size;
            }
        }
    }

    inline void move_value_to_first(std::vector<int>& vec,
                                    const std::size_t delete_count,
                                    const std::size_t valid_count)
    {
        for (std::size_t i = 0; i < valid_count; ++i)
        {
            vec[i] = vec[delete_count + i];
        }
        vec.erase(vec.begin() + valid_count, vec.end());
    }
}  // namespace RadixSort