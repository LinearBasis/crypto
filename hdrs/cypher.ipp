#pragma once
#include <bitset>
#include <array>
#include "key_generation.ipp"

template <size_t encrypted_size, size_t decrypted_size, size_t key_size, size_t key_number>
class ISymmertyCypher
{
public:
    typedef std::bitset<key_size>               key_type;
    typedef std::array<key_type, key_number>    key_array_type;

    typedef std::bitset<encrypted_size>         encrypted_block_type;
    typedef std::bitset<decrypted_size>         decrypted_block_type;
    
    typedef encrypted_block_type                init_vector_type;

    virtual encrypted_block_type encrypt_block(const decrypted_block_type& block, 
        const key_array_type &key_array) const = 0;
    virtual decrypted_block_type decrypt_block(const encrypted_block_type& block, 
        const key_array_type &key_array) const = 0;
};