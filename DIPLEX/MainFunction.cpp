// main.cpp
#include <iostream>
#include "ConversionTable.h"
#include "Compiler.h"

int main() {
    // Initialize Conversion Table
    ConversionTable::initialize();

    // Example DIPLEX code
    std::string code = "start var a = 10; var b = 20; var sum = a + b; output(sum); stop";

    // Compile and execute the code
    Compiler compiler;
    compiler.compileAndExecute(code);

    return 0;
}
