// Parser.h
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <iostream>
#include "ConversionTable.h"

class Parser {
public:
    // Converts DIPLEX code tokens into hexadecimal code
    void parse(const std::vector<std::string>& tokens) {
        for (const auto& token : tokens) {
            std::string hexCode = ConversionTable::getHexCode(token);
            std::cout << "Token: " << token << " -> Hex: " << hexCode << std::endl;
        }
    }
};

#endif // PARSER_H
