#pragma once
#include <bitset>
#include <cstdlib>

template <size_t n, size_t size>
std::bitset<size> subset(const std::bitset<n> &number, size_t min, size_t max)
{
    // return std::bitset<max - min>(number.to_string().substr(min, max - min));
    std::bitset<size>  ans;

    for (size_t i = min; i < max; ++i)
    {
        ans[i - min] = number[i];
    }
    return (ans);
}
