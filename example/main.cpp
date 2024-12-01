#include <iostream>
#include <bitset>
#include <vector>
#include <utility>
#include <cstdint>

#include "DES_functions.h"


int main() {
	
	// key as array of hex values
	std::vector<uint8_t> key = { 0xA, 0x3, 0xB, 0x5, 0xC, 0x2, 0xD, 0x6, 0x1, 0xA, 0x3, 0xC, 0x5, 0xD, 0x6, 0x2 };

	// convert key to bits
	std::bitset<64> binaryKey = DES_library::to64Bit(key);
	
	// Message in Hex
	std::vector<uint8_t> messageHex = { 0x5, 0xC, 0x1, 0xD, 0x3, 0x6, 0xA, 0x2, 0xB, 0x3, 0xA, 0x5, 0xD, 0x1, 0x6, 0xC };

	// Convert message to binary
	std::bitset<64> messageBit = DES_library::to64Bit(messageHex);	
	
	// Encrypt message
	std::bitset<64> encryptedMessage = DES_library::encrypt(messageBit, binaryKey);

	// Display ciphertext
	std::cout << "ciphertext: " << encryptedMessage << std::endl;

	// Decrypt ciphertext. Same key is used to decrypt message.
	std::bitset<64> decryptedMessage = DES_library::decrypt(encryptedMessage, binaryKey);

	// Convert to vector
	auto decryptedMessageHex = DES_library::toHex(decryptedMessage);

	// Display vector
	std::cout << std::hex;
	for (auto item: decryptedMessageHex) {
		std::cout << (int)item << " ";
	} 
	std::cout << std::dec << std::endl;

    return 0;
}
