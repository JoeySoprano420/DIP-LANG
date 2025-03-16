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

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cctype>

// Token structure
struct Token {
    std::string type;
    std::string value;
};

// Conversion table mapping DIPLEX to C++
std::unordered_map<std::string, std::string> conversionTable = {
    {"output", "std::cout"},
    {"var", "int"},
    {"fn", "function"},
    {"start", "block_start"},
    {"stop", "block_end"}
};

// Lexer: Tokenizes DIPLEX code
std::vector<Token> lexer(const std::string &code) {
    std::vector<Token> tokens;
    std::string temp;
    bool insideBlock = false;

    for (size_t i = 0; i < code.size(); ++i) {
        char c = code[i];

        // Handle comments (lines starting with #)
        if (c == '#' && (i == 0 || std::isspace(code[i-1]))) {
            while (i < code.size() && code[i] != '\n') ++i; // Skip comment line
            continue;
        }

        // Handle 'start' and 'stop' as block markers
        if (code.substr(i, 5) == "start") {
            tokens.push_back({"start", "start"});
            i += 4;  // Skip "start"
        } else if (code.substr(i, 4) == "stop") {
            tokens.push_back({"stop", "stop"});
            i += 3;  // Skip "stop"
        }
        else if (std::isspace(c) || c == ';') {
            // If there’s whitespace or semicolon, push the token if it’s not empty
            if (!temp.empty()) {
                tokens.push_back({"word", temp});
                temp.clear();
            }
        } else {
            // Collect characters into token for words/commands
            temp += c;
        }
    }

    // Push the last token if there’s one left
    if (!temp.empty()) tokens.push_back({"word", temp});
    return tokens;
}

// Parser: Creates an Abstract Syntax Tree (AST) and handles start/stop blocks
void parser(std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        if (token.type == "start") {
            std::cout << "Start Block: Begin execution group." << std::endl;
        } else if (token.type == "stop") {
            std::cout << "Stop Block: End execution group." << std::endl;
        } else {
            // Convert DIPLEX commands using the conversion table
            auto it = conversionTable.find(token.value);
            if (it != conversionTable.end()) {
                std::cout << it->second << " ";
            } else {
                std::cout << token.value << " ";
            }
        }
    }
    std::cout << std::endl;
}

// Simple Execution context
std::unordered_map<std::string, int> variables;

// Execute function based on parsed tokens
void execute(const std::vector<Token>& tokens) {
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
void interpret(const std::string& code) {
    std::vector<Token> tokens = lexer(code);
    parser(tokens);
    execute(tokens);
}

int main() {
    // Example DIPLEX code with comments and start/stop
    std::string diplexCode = R"(
        # This is a comment
        start
            var x = 10;
            var y = 20;
            var sum = x + y;
            output(sum);
        stop
    )";

    interpret(diplexCode);
    return 0;
}
