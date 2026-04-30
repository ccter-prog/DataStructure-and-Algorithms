#ifndef EXPECTED_H
#define EXPECTED_H

#include "heap.h"

typedef enum
{
    EXPECTED_ERROR,  // 必须为 0，用于 if (result.has_value) 的隐式布尔判断
    EXPECTED_OK      // 必须为 1，表示成功状态
} expected_status_t;

struct expected
{
    union
    {
        Elem value;
        const char *error;
    };
    expected_status_t has_value;
};

#endif