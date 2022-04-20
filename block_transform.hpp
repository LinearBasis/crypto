#pragma once

#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <set>


#define MAX_BLOCK_SIZE 512
#define DEBUG true

template <size_t size>
std::bitset<size>   p_block(std::bitset<size> begin_state, std::array<size_t, size> rule)
{
    std::bitset<size>   end_state;
    for (int i = 0; i < size; ++i)
        end_state[rule[i]] = begin_state[i];
    return (end_state);
}

std::bitset<MAX_BLOCK_SIZE> __bitset_for_test;

template <size_t size>
bool    test_rule_p_block(const std::array<size_t, size> &rule)
{
    if (size > MAX_BLOCK_SIZE)
    {
        #ifdef DEBUG
            std::cerr << "size \n";
        #endif
        return false;
    }
    for (int i = 0; i < rule.size(); ++i)
    {
        __bitset_for_test[i] = 0;
        if (rule[i] >= size)
        {
            #ifdef DEBUG
                std::cerr << "index in rule is more than blocksize\n";
            #endif
            return false;
        }
    }
    for (int i = 0; i < rule.size(); ++i)
    {
        if (!test_rule_p_block(rule))
        {
            return false;
        }

        if (__bitset_for_test[rule[i]] == 1)
        {
            #ifdef DEBUG
                std::cerr << "repeated values\n";
            #endif
            return false;
        }
        __bitset_for_test[rule[i]] = 1;
    }
    return true;
}

template <size_t size>
bool    test_p_block(std::bitset<size> begin_state,
                        std::array<size_t, size> rule, std::bitset<size> end_state)
{
    for (int i = 0; i < size; ++i)
    {
        if (begin_state[i] != end_state[rule[i]])
        {
            #ifdef DEBUG
                std::cerr << "transforming from " << i << " to " << rule[i] << " not done\n";
            #endif
            return false;
        }
    }
    return true;
}


template <size_t size>
struct bitset_less
{
    bool    operator()(const std::bitset<size> left, const std::bitset<size> right) const
    {
        return (left.to_ullong() < right.to_ullong());
    }
};

template <size_t begin_size, size_t end_size>
using  rule_map = std::map<std::bitset<begin_size>, std::bitset<end_size>,
                                bitset_less<begin_size> >;

template <size_t size, size_t s_begin_size, size_t s_end_size>
std::bitset<size / s_begin_size * s_end_size>
    s_block(std::bitset<size> begin_state, rule_map<s_begin_size, s_end_size> rule)
{
    if (size % s_begin_size != 0)
    {
        throw std::invalid_argument("size or s_size is not valid");
    }
    if (rule.size() != (1 << s_begin_size))
    {
        throw std::invalid_argument("rule is not valid");
    }

    const int num_of_s_blocks = size / s_begin_size;
    std::bitset<s_begin_size>   key_bitset;
    std::bitset<size / s_begin_size * s_end_size> end_state;

    for (int number_of_block = 0; number_of_block < num_of_s_blocks; ++number_of_block)
    {
        for (int s_block_index = 0; s_block_index < s_begin_size; ++s_block_index)          //вычленяем из числа блок размера s_begin_size
        {
            key_bitset[s_block_index] = begin_state[number_of_block * s_begin_size + s_block_index];
        }
        for (int s_block_index = 0; s_block_index < s_end_size; ++s_block_index)
        {
            end_state[number_of_block * s_end_size + s_block_index] = rule[key_bitset][s_block_index];
        }
    }
    return end_state;
}

template <size_t s_begin_size, size_t s_end_size>
bool    test_s_block_rule(rule_map<s_begin_size, s_end_size> rule)
{
    std::set<std::bitset<s_end_size> >  set_of_values;

    if (rule.size() != (1 << s_begin_size) || s_begin_size > 64)
    {
        #ifdef DEBUG
            std::cerr << "invalid size of rule\n";
        #endif
        return false;
    }
    for (const auto &i : rule)
    {
        if (set_of_values.find(i.second()) != set_of_values.end())
        {
            #ifdef DEBUG
                std::cerr << "repeat values\n";
            #endif
            return false;
        }
        set_of_values.insert(i.second());
    }
    return true;
}

template <size_t size, size_t s_begin_size, size_t s_end_size>
bool    test_s_block(std::bitset<size> begin_state, rule_map<s_begin_size, s_end_size> rule,
            std::bitset<size / s_begin_size * s_end_size>  end_state)
{
    return true;
}

