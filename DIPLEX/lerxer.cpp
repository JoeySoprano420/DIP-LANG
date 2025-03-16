// Lexer.h
#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Lexer {
public:
    // Tokenizes the DIPLEX source code
    std::vector<std::string> tokenize(const std::string& code) {
        std::vector<std::string> tokens;
        std::stringstream ss(code);
        std::string word;
        
        while (ss >> word) {
            tokens.push_back(word);
        }

        return tokens;
    }
};

#endif // LEXER_H
