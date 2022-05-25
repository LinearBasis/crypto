#include <iostream>
#include <vector>
#include <bitset>
#include <stdexcept>
#include <map>
#include <cmath>

#include "../hdrs/bitset_operations.hpp"
#include "../hdrs/PKCS7.hpp"

int main()
{
    std::bitset<32>  test(0xFFFF0000);

    std::cout << test << std::endl << PKCS7<32>().padding(test, 16) << std::endl;

}