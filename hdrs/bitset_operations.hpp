#pragma once
#include <bitset>
#include <cstdlib>




// cdef123456
// 9876543210

// 123456
// 543210

template <size_t n, size_t size>
std::bitset<size> subset(const std::bitset<n> &number, size_t min, size_t max)
{
    std::bitset<size>  ans;

    for (size_t i = min; i < max; ++i)
    {
        ans[size - 1 - (i - min)] = number[n - 1 - i];
    }
    return (ans);
}
