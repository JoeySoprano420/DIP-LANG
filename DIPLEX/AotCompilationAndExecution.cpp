// Compiler.h
#ifndef COMPILER_H
#define COMPILER_H

#include "Lexer.h"
#include "Parser.h"
#include "CodeGenerator.h"
#include "Optimizer.h"

class Compiler {
public:
    void compileAndExecute(const std::string& code) {
        // Tokenization
        Lexer lexer;
        std::vector<std::string> tokens = lexer.tokenize(code);
        
        // Parsing
        Parser parser;
        parser.parse(tokens);

        // Code Generation
        CodeGenerator codeGen;
        for (const auto& token : tokens) {
            std::string hexCode = ConversionTable::getHexCode(token);
            codeGen.generateBinaryCode(hexCode);
        }

        // Optimization (if needed)
        Optimizer optimizer;
        std::vector<std::string> binaryCode = {"BinaryCode1", "BinaryCode2"}; // Placeholder
        optimizer.optimize(binaryCode);

        // Compile to executable binary (skipped for simplicity)
        std::cout << "Compilation complete. Executing binary...\n";
        
        // Execute the generated binary code (would be specific to system architecture)
    }
};

#endif // COMPILER_H
