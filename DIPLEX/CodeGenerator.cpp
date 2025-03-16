// CodeGenerator.h
#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <bitset>

class CodeGenerator {
public:
    // Convert a hexadecimal string to binary
    std::string hexToBinary(const std::string& hex) {
        unsigned int n;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> n;
        return std::bitset<32>(n).to_string();  // Return 32-bit binary representation
    }

    // Generate machine code (for simplicity, we're converting hex to binary)
    void generateBinaryCode(const std::string& hexCode) {
        std::string binary = hexToBinary(hexCode);
        std::cout << "Hex: " << hexCode << " -> Binary: " << binary << std::endl;
    }
};

#endif // CODE_GENERATOR_H
