// CodeGenerator.h
#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include <string>
#include <bitset>
#include <fstream>
#include <iostream>

class CodeGenerator {
public:
    // Convert a hexadecimal string to machine code (assembly format)
    std::string hexToAssembly(const std::string& hex) {
        // In a real scenario, you would map hex to assembly instructions.
        // This is a simple mock-up for educational purposes.
        unsigned int n;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> n;
        return "MOV R0, #" + std::to_string(n); // Basic Assembly-like Code
    }

    // Generate assembly code
    void generateAssemblyCode(const std::string& hexCode, const std::string& outputFileName) {
        std::ofstream outFile(outputFileName);
        
        if (!outFile.is_open()) {
            std::cerr << "Error opening output file for assembly code.\n";
            return;
        }
        
        std::string assemblyCode = hexToAssembly(hexCode);
        outFile << assemblyCode << "\n";
        outFile.close();
        
        std::cout << "Assembly code generated in " << outputFileName << std::endl;
    }
};

#endif // CODE_GENERATOR_H
