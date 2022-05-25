#pragma once

#include "padding.ipp"

template <size_t max_block_size>
class PKCS7 : public IPadder<max_block_size>
{
public:
    std::bitset<max_block_size>
        padding(const std::bitset<max_block_size> &begin_state, size_t block_size)
            const override
    {
        std::bitset<max_block_size> ans(0);
        if (max_block_size == block_size)
        {
            std::bitset<8>  added_byte(8);
            for (size_t i = 0; i < max_block_size; ++i)
            {
                ans[i] = added_byte[i % 8];
            }
        }
        else
        {
            std::cout << "a" << std::endl;
            std::bitset<8>  added_byte((max_block_size - block_size) / 8);
            for (size_t i = 0; i < block_size; ++i)
            {
                ans[i] = begin_state[i];
            }
            for (size_t i = block_size; i < max_block_size; ++i)
            {
                ans[i] = added_byte[i % 8];
            }
        }
        return ans;
    }    
};