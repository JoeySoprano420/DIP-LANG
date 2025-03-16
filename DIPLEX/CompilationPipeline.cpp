// In the Compiler class
void compileAndExecuteFromFile(const std::string& filename) {
    // Tokenization from file
    Lexer lexer;
    std::vector<std::string> tokens = lexer.tokenizeFromFile(filename);

    if (tokens.empty()) {
        std::cerr << "No tokens to compile. Exiting..." << std::endl;
        return;
    }

    // Parsing
    Parser parser;
    parser.parse(tokens);

    // Code Generation (Generate Assembly)
    CodeGenerator codeGen;
    for (const auto& token : tokens) {
        std::string hexCode = ConversionTable::getHexCode(token);
        std::string assemblyFile = "output.asm";
        codeGen.generateAssemblyCode(hexCode, assemblyFile);

        // Compile assembly to machine code
        codeGen.compileWithGCC(assemblyFile);
    }
}
