#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

// Token structure
struct Token {
    std::string type;
    std::string value;
};

// Lexer: Tokenizes DIPLEX code
std::vector<Token> lexer(const std::string &code) {
    std::vector<Token> tokens;
    std::string temp;
    for (char c : code) {
        if (std::isspace(c) || c == ';' || c == '(' || c == ')') {
            if (!temp.empty()) {
                tokens.push_back({"word", temp});
                temp.clear();
            }
            if (c == '(' || c == ')') {
                tokens.push_back({"symbol", std::string(1, c)});
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) tokens.push_back({"word", temp});
    return tokens;
}

// Parser: Creates an Abstract Syntax Tree (AST)
void parser(const std::vector<Token> &tokens) {
    for (const auto &token : tokens) {
        std::cout << "Token: " << token.type << ", Value: " << token.value << std::endl;
    }
}

// Simple Execution context
std::unordered_map<std::string, int> variables;

// Execute function based on parsed tokens
void execute(const std::vector<Token> &tokens) {
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (tokens[i].value == "var") {
            // Variable assignment
            std::string varName = tokens[i + 1].value;
            int value = std::stoi(tokens[i + 3].value);
            variables[varName] = value;
            i += 3;
        } else if (tokens[i].value == "output") {
            // Output function
            std::string varName = tokens[i + 1].value;
            std::cout << variables[varName] << std::endl;
            i += 1;
        }
    }
}

// Main function for interpreting DIPLEX
void interpret(const std::string &code) {
    std::vector<Token> tokens = lexer(code);
    parser(tokens);
    execute(tokens);
}

int main() {
    std::string diplexCode = R"(var x = 10; var y = 20; output(x);)";
    interpret(diplexCode);
    return 0;
}
