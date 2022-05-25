#pragma once

#include <bitset>
#include <map>

template <size_t size>
struct bitset_less
{
    bool    operator()(const std::bitset<size>& left, const std::bitset<size>& right) const
    {
        return (left.to_ullong() < right.to_ullong());
    }
};

template <size_t begin_size, size_t end_size>
using  rule_map = std::map<std::bitset<begin_size>, std::bitset<end_size>,
                                bitset_less<begin_size> >;


template <size_t size, size_t s_begin_size, size_t s_end_size>
std::bitset<size / s_begin_size * s_end_size>
    s_block(const std::bitset<size>& begin_state, rule_map<s_begin_size, s_end_size>& rule)
{
    if (size % s_begin_size != 0)
    {
        throw std::invalid_argument("size or s_size is not valid");
    }
    if (rule.size() != (1 << s_begin_size))
    {
        throw std::invalid_argument("rule is not valid");
    }


    std::bitset<s_begin_size>   key_bitset;
    std::bitset<s_end_size>     value_bitset; 
    std::bitset<size / s_begin_size * s_end_size> end_state;


    const int num_of_s_blocks = size / s_begin_size;

    for (int number_of_block = 0; number_of_block < num_of_s_blocks; ++number_of_block)
    {
        for (int s_block_index = 0; s_block_index < s_begin_size; ++s_block_index)          //вычленяем из числа блок размера s_begin_size
            key_bitset[s_block_index] =
                begin_state[number_of_block * s_begin_size + s_block_index];
        
        value_bitset = rule[key_bitset];
        for (int s_block_index = 0; s_block_index < s_end_size; ++s_block_index)
            end_state[number_of_block * s_end_size + s_block_index] =
                value_bitset[s_block_index];
    }
    return end_state;
}

template<size_t s_begin_size, size_t s_end_size>
rule_map<s_begin_size, s_end_size> create_rules(
    std::vector<std::string> begin_states, std::vector<std::string> end_states)
{
    rule_map<s_begin_size, s_end_size> rule; 
    if (begin_states.size() != end_states.size())
    {
        #ifdef DEBUG
            std::cerr << "invalid states\n";
        #endif
        return rule_map<s_begin_size, s_end_size>(); 
    }
    for (int i = 0; i < end_states.size(); ++i)
    {
        rule[std::bitset<s_begin_size>(begin_states[i])] = std::bitset<s_end_size>(end_states[i]);
    }
    return rule;
}