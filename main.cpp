#include <iostream>
#include <vector>
#include <bitset>
#include <stdexcept>
#include <map>
#include <cmath>

// using namespace std;
#include "block_transform.hpp"

bool    test_p_block_on_cases()
{
    std::vector<std::string>    cases = {"0000000000", "0100010011", "1010101010", "1010101010"};
    std::vector<std::array<size_t, 10> > rules = {
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
            {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 
            {1, 5, 4, 3, 7, 8, 2, 6, 9, 0}, 
    };

    for (int i = 0; i < cases.size(); ++i)
    {
        for (int j = 0; j < rules.size(); ++j)
        {
            std::bitset<10> begin_state(cases[i]);
            std::bitset<10> result = p_block(begin_state, rules[j]);
            if (!test_p_block(begin_state, rules[j], result))
            {
                std::cerr << "bad func" << std::endl;
                return false;
            }
        }
    }
    return true;
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

bool    test_s_block_on_cases()
{
    std::bitset<8>  begin_state("00011011");

    rule_map<2, 2>  rule = create_rules<2, 2>(
        std::vector<std::string>({"00", "01", "10", "11"}),
        std::vector<std::string>({"11", "10", "01", "00"})
    );

    rule_map<1, 1>  rule2 = create_rules<1, 1>(
        std::vector<std::string>({"0", "1"}),
        std::vector<std::string>({"1", "0"})
    );


    std::bitset<8>  end_state = s_block(begin_state, rule);
    std::cout << end_state << std::endl;

    std::cout << s_block(begin_state, rule2) << std::endl;
    return true;
}


int main()
{
    std::cout << test_s_block_on_cases() << std::endl;
}