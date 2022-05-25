#pragma once
#include <bitset>

template <size_t begin_size, size_t end_size, size_t key_size>
class ICypherTransform
{
public:
    typedef std::bitset<begin_size>             block_type;
    typedef std::bitset<end_size>               transformed_block_type;
    typedef std::bitset<key_size>               key_type;

    virtual transformed_block_type  transform(const block_type& block,
            const key_type& key) const = 0;
};