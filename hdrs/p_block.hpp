#pragma once

#include <bitset>
#include <array>

template <size_t size>
std::bitset<size>   p_block(const std::bitset<size>& begin_state, const std::array<size_t, size>& rule)
{
    std::bitset<size>   end_state;
    std::cout << begin_state << std::endl;
    std::cout << std::endl;
    for (int i = size - 1; i >= 0; --i)
    {
        end_state[i] = begin_state[size - 1 - rule[size - i - 1]];
    }
    return (end_state);
}

template <size_t begin_size, size_t end_size>
std::bitset<end_size>   p_block(const std::bitset<begin_size>& begin_state, const std::array<size_t, end_size>& rule)
{
    std::bitset<end_size>   end_state;
    std::cout << begin_state << std::endl;
    std::cout << std::endl;
    for (int i = end_size - 1; i >= 0; --i)
    {
        end_state[i] = begin_state[begin_size - 1 - rule[end_size - i - 1]];
    }
    return (end_state);
}