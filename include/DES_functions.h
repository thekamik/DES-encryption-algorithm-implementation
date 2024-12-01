#ifndef DES_FUNCTIONS_H
#define DES_FUNCTIONS_H

#include <iostream>
#include <bitset>
#include <vector>
#include <utility>
#include <cstdint>

namespace DES_library {

    std::bitset<64> desAlgorithm(const std::bitset<64>& message, const std::vector<std::bitset<48>>& roundKey);

    std::bitset<32> sboxSubstituting(const std::bitset<48>& message);   // helper function

    std::bitset<64> encrypt(const std::bitset<64>& message, const std::bitset<64>& binaryKey);
    std::bitset<64> decrypt(const std::bitset<64>& message, const std::bitset<64>& binaryKey);

    std::vector<std::bitset<48>> generateRoundKey(const std::bitset<64>& binaryKey);

    std::bitset<64> to64Bit(const std::vector<uint8_t>& message);

    std::vector<uint8_t> toHex(const std::bitset<64>& message);

    std::vector<uint8_t> encryptString(const std::string& message, const std::bitset<64>& binaryKey);
    std::string decryptString(const std::vector<uint8_t>& encryptedMessage, const std::bitset<64>& binaryKey);

}
#endif