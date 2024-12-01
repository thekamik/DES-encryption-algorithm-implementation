#include "DES_functions.h"
#include "DES_constants.h"
#include "DES_templates.h"

#include <iostream>
#include <bitset>
#include <vector>
#include <utility>
#include <cstdint>
#include <algorithm>

namespace DES_library {

    std::bitset<32> sboxSubstituting(const std::bitset<48>& message) {
        std::bitset<32> outputMessage;

        for (int i = 0; i < 8; i++) {
            // Extract row bits from the message. Bitset works in reverse order, so we start counting from the end.
            std::bitset<2> row;
            row[1] = message[(47 - i * 6)];	// 0
            row[0] = message[(42 - i * 6)];	// -5

            // Extract column bits from the message
            std::bitset<4> col;
            col[3] = message[(46 - i * 6)];	// -1
            col[2] = message[(45 - i * 6)];	// -2
            col[1] = message[(44 - i * 6)];	// -3
            col[0] = message[(43 - i * 6)];	// -4

            // Lookup S-box value
            int val = sBoxTable[i][row.to_ulong()][col.to_ulong()];
            std::bitset<4> binVal(val);

            // Write S-box result to the correct position in the output
            for (int j = 0; j < 4; j++) {
                outputMessage[(31 - (i * 4)) - j] = binVal[3 - j];
            }
        }

        return outputMessage;
    }

    std::bitset<64> desAlgorithm(const std::bitset<64>& message, const std::vector<std::bitset<48>>& roundKey) {

        // Initial Permutation
        std::bitset<64> bitMessage = permute<64, 64>(message, initialPermutationTable);

        // Split the vector into two parts
        std::bitset<32> right = slice<64, 32>(bitMessage, 0, 32);
        std::bitset<32> left = slice<64, 32>(bitMessage, 32, 32);

        for (int i = 0; i < 16; i++) {
            // Expansion D-box: Expanding the 32 bits data into 48 bits
            std::bitset<48> right_expanded = permute<48, 32>(right, eBitSelectionTable);

            // XOR RoundKey[i] and right_expanded
            std::bitset<48> xor_x = right_expanded ^ roundKey[i];

            // S-boxex: substituting the value from s-box table by calculating row and column
            std::bitset<32> sbox_bits = sboxSubstituting(xor_x);

            // Straight D-box: After substituting rearranging the bits
            std::bitset<32> sbox_bits_permuted = permute<32, 32>(sbox_bits, permutationTable);

            // XOR left and sbox_bits_permuted
            std::bitset<32> result = left ^ sbox_bits_permuted;
            left = result;

            // Swapper
            if(i != 15) {
                std::swap(left, right);
            }
        }

        // Combination
        std::string combined = left.to_string() + right.to_string();
        std::bitset<64> combine(combined);

        // Final permutation: final rearranging of bits to get cipher text
        std::bitset<64> cipher_text = permute<64, 64>(combine, finalPermutationTable);

        return cipher_text;
    }

    std::bitset<64> encrypt(const std::bitset<64>& message, const std::bitset<64>& binaryKey) {

        // Generate round key
        std::vector<std::bitset<48>> roundKey = DES_library::generateRoundKey(binaryKey);

        return desAlgorithm(message, roundKey);
    }

    std::bitset<64> decrypt(const std::bitset<64>& message, const std::bitset<64>& binaryKey) {

        // Generate round key
        std::vector<std::bitset<48>> roundKey = DES_library::generateRoundKey(binaryKey);

        // Reverse round key
        std::reverse(roundKey.begin(), roundKey.end());

        return desAlgorithm(message, roundKey);
    }

    std::vector<std::bitset<48>> generateRoundKey(const std::bitset<64>& binaryKey) {

        // getting 56 bit key from 64 bit using the parity bits
        std::bitset<56> keyBit = permute<56, 64>(binaryKey, permutedChoiceTable);

        // Splitting
        std::bitset<28> right = slice<56, 28>(keyBit, 0, 28);
        std::bitset<28> left = slice<56, 28>(keyBit, 28, 28);
        

        std::vector<std::bitset<48>> rkb;
        for (int i = 0; i < 16; i++) {
            // Shifting the bits by nth shifts by checking from shift table
            left = circularLeftShift(left, shiftTable[i]);
            right = circularLeftShift(right, shiftTable[i]);

            // Combination
            std::string combined = left.to_string() + right.to_string();
            std::bitset<56> combine(combined);

            // Compression of key from 56 to 48 bits
            std::bitset<48> round_key = permute<48, 56>(combine, permutedChoiceTable2);

            rkb.push_back(round_key);
        }

        return rkb;
    }

    std::bitset<64> to64Bit(const std::vector<uint8_t>& message) {
        std::bitset<64> binaryMessage;

        // Check if message have right size
        if (message.size() > 16) {
            throw std::runtime_error("Message too long");
        }

        for (size_t i = 0; i < message.size(); i++) {
            // Check if number is in range
            if (message[i] > 15 || message[i] < 0) {
                throw std::runtime_error("Incorrect value");
            }

            // Convert number to binary
            std::bitset<4> numBin(message[15 - i]);

            // push bits to message
            for (int j = 0; j < 4; j++) {
                binaryMessage[i * 4 + j] = numBin[j];
            }
        }

        return binaryMessage;
    }

    std::vector<uint8_t> toHex(const std::bitset<64>& message) {
        std::vector<uint8_t> outputMessage;
        outputMessage.reserve(16);

        for (int i = 0; i < 64; i += 4) {
            // Convert to number
            std::bitset<4> nextNum = slice<64, 4>(message, i, 4).to_ulong();
            int num = static_cast<int>(nextNum.to_ulong());
            outputMessage.push_back(num);
        }
        
        std::reverse(outputMessage.begin(), outputMessage.end());

        return outputMessage;
    }

}