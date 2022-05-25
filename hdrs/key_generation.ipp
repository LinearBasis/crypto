#pragma once
#include <bitset>
#include <array>

template <size_t init_key_size, size_t key_size, size_t keys_number>
class   IKeyGen
{
public:
    typedef std::bitset<init_key_size>          init_key_type;
    typedef std::bitset<key_size>               key_type;
    typedef std::array<keys_number, key_type>   key_array_type;

    virtual ~IKeyGen() {}

    virtual key_array_type generate_keys(const init_key_type& init_key ) const = 0;

    
};
