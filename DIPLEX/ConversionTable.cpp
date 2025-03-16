// ConversionTable.h
#ifndef CONVERSION_TABLE_H
#define CONVERSION_TABLE_H

#include <unordered_map>
#include <string>

class ConversionTable {
public:
    // Mapping of DIPLEX keywords to hexadecimal values
    static std::unordered_map<std::string, std::string> table;

    // Populate the conversion table (this would be read from the file in a real implementation)
    static void initialize() {
        table["start"] = "0x1";
        table["stop"] = "0x2";
        table["var"] = "0x3";
        table["output"] = "0x4";
        // Add more mappings as needed
    }

    // Lookup function for keyword conversion
    static std::string getHexCode(const std::string& keyword) {
        return table[keyword];
    }
};

// Initialize the static table
std::unordered_map<std::string, std::string> ConversionTable::table;

#endif // CONVERSION_TABLE_H
