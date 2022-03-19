#include <iostream>
#include <vector>
#include <bitset>
#include <stdexcept>
#include <map>
#include <cmath>

using namespace std;

template <size_t size>
std::bitset<size>   p_block(std::bitset<size> begin_state, std::vector<int> rule)
{
    if (rule.size() != size)
        throw std::invalid_argument("rule is not valid");

    std::array<bool, size>  test = {false};
    std::bitset<size>   end_state;

    for (int i = 0; i < size; ++i)
    {
        if (rule[i] >= size || rule[i] < 0 || test[rule[i]])
            throw std::invalid_argument("rule is not valid");
        test[rule[i]] = true;
        end_state[i] = begin_state[rule[i]];
    }
    return (end_state);
}

template <size_t size>
struct bitset_less
{
    bool    operator()(const std::bitset<size> left, const std::bitset<size> right) const
    {
        return (left.to_ullong() < right.to_ullong());
    }
};

template <size_t size>
using  rule_map = std::map<std::bitset<size>, std::bitset<size>, bitset_less<size> >;

template <size_t size, size_t s_size>
std::bitset<size>   s_block(std::bitset<size> begin_state, rule_map<s_size> rule)
{
    if (size % s_size != 0)
    {
        throw std::invalid_argument("size or s_size is not valid");
    }
    if (rule.size() != (1 << s_size))
    {
        throw std::invalid_argument("rule is not valid");
    }

    std::bitset<s_size> tmp;
    const int num_of_s_blocks = size / s_size;
    for (int i = 0; i < num_of_s_blocks; ++i)
    {
        for (int j = 0; j < s_size; ++j)
        {
            tmp[j] = begin_state[i * s_size + j];
        }
        for (int j = 0; j < s_size; ++j)
        {
            begin_state[i * s_size + j] = rule[tmp][j];
        }
    }
    return begin_state;
}




int main()
{
    std::bitset<8>  test("00011011");
    rule_map<2> rule = { {  std::bitset<2>("00"), std::bitset<2>("01") },
                         {  std::bitset<2>("01"), std::bitset<2>("10") },
                         {  std::bitset<2>("10"), std::bitset<2>("11") },
                         {  std::bitset<2>("11"), std::bitset<2>("00") } };
    std::cout << test << "\n" << s_block(test, rule) << std::endl;
}