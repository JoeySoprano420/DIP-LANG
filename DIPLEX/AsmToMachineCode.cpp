// CodeGenerator.h (continue from previous code)
#include <cstdlib>

// Method to invoke system compiler (e.g., GCC or Clang)
void compileWithGCC(const std::string& assemblyFile) {
    std::string command = "gcc -o output_binary " + assemblyFile;
    int result = std::system(command.c_str());
    
    if (result == 0) {
        std::cout << "Successfully compiled to machine code (binary).\n";
    } else {
        std::cerr << "Compilation failed!\n";
    }
}
