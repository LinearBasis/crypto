#pragma once
#include "cypher.ipp"
#include "key_generation.ipp"
#include "cypher_transform.ipp"

enum class cypher_mode
{
    ECB,
    CBC,
    CFB,
    OFB,
    CTR,
    RD,
    RDH
};



template <size_t encrypted_size, size_t decrypted_size,
    size_t key_size, size_t key_number>
class SymmertyCypher
{

private:
    init_vector_type    iv;
    cypher_mode         mode;
    key_array_type      key_array;
    key_type            key;

    ICypherTransform    transformer_func;
    ISymmertyCypher     cypher;
    IKeyGen             key_generator;
    

public:
    SymmertyCypher()
    {
        std::cout << "invalid v\n";
    }

    template <size_t message_size>

    
};