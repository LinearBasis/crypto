#pragma once
#include "bitset_operations.hpp"

template <size_t max_block_size>
class IPadder
{
public:
    virtual std::bitset<max_block_size>
        padding(const std::bitset<max_block_size> &begin_state, size_t block_size)
            const = 0;
};