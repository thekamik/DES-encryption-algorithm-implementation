#ifndef DES_TEMPLATES_H
#define DES_TEMPLATES_H

#include <iostream>
#include <bitset>
#include <vector>
#include <utility>
#include <cstdint>

namespace DES_library {

    template <size_t outputSize, size_t inputSize>
    std::bitset<outputSize> permute(const std::bitset<inputSize>& message, const std::vector<uint8_t>& indices) {

        // Create an empty string to store the permuted result
        std::bitset<outputSize> permuted;

        // Perform the permutation
        for (int i = 0; i < outputSize; i++) {
            int sourceIndex = indices[i] - 1; // Adjust from 1-based to 0-based indexing
            if (sourceIndex < 0 || sourceIndex >= inputSize) {
                throw std::out_of_range("Index out of range in indices");
            }

            // Save the result, bitset work in reverse order
            permuted[outputSize - 1 - i] = message[inputSize - 1 - sourceIndex];
        }

        // Convert the permuted string back to a bitset
        return permuted;
    }

    template <size_t N, size_t M>
    std::bitset<M> slice(const std::bitset<N>& bits, size_t start, size_t length) {
        if (start + length > N) {
            throw std::out_of_range("Slice out of bounds");
        }

        std::bitset<M> result;
        for (size_t i = 0; i < length; ++i) {
            result[i] = bits[start + i];
        }
        return result;
    }

    template <size_t N>
    std::bitset<N> circularLeftShift(const std::bitset<N>& bits, size_t shift) {
        // Normalize the shift to be within the range [0, N)
        shift %= N;

        // Get the bits that "fall off" the left
        std::bitset<N> overflow = bits >> (N - shift);

        // Perform the left shift and add the "overflow" bits back on the right
        return (bits << shift) | overflow;
    }
}

#endif