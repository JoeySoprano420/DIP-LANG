// main.cpp
#include <iostream>
#include "ConversionTable.h"
#include "Compiler.h"

int main() {
    // Initialize Conversion Table
    ConversionTable::initialize();

    // Example DIPLEX source file path
    std::string filename = "example.diplex";

    // Compile and execute the code from the file
    Compiler compiler;
    compiler.compileAndExecuteFromFile(filename);

    return 0;
}
