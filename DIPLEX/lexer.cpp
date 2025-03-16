// Lexer.h
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

class Lexer {
public:
    // Tokenizes DIPLEX source code from a file
    std::vector<std::string> tokenizeFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::string> tokens;
        
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return tokens;
        }
        
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string word;
            while (ss >> word) {
                tokens.push_back(word);
            }
        }

        file.close();
        return tokens;
    }
};

#endif // LEXER_H
