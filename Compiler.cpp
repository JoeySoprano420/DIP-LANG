#include <iostream>
#include <regex>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <memory>

// Token types based on DIP-LANG syntax
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    SYMBOL,
    STRING,
    UNKNOWN
};

// Mapping keywords to token type names
std::map<std::string, TokenType> tokenMap = {
    {"if", KEYWORD},
    {"else", KEYWORD},
    {"while", KEYWORD},
    {"return", KEYWORD},
    {"func", KEYWORD},
    {"var", KEYWORD},
    {"struct", KEYWORD},
    {"import", KEYWORD},
    {"export", KEYWORD},
    {"class", KEYWORD},
    {"for", KEYWORD},
    {"break", KEYWORD},
    {"continue", KEYWORD}
};

// Regular expression patterns for each token type
std::map<TokenType, std::regex> patterns = {
    {KEYWORD, std::regex(R"(\b(if|else|while|return|func|var|struct|import|export|class|for|break|continue)\b)")},
    {IDENTIFIER, std::regex(R"(\b[a-zA-Z_][a-zA-Z0-9_]*\b)")},
    {NUMBER, std::regex(R"(\b\d+(\.\d+)?\b)")},
    {OPERATOR, std::regex(R"([+\-*/=<>!&|])")},
    {SYMBOL, std::regex(R"([(){},;\[\]])")},
    {STRING, std::regex(R"(".+?")")}
};

struct Token {
    TokenType type;
    std::string value;
};

// Lexer: Converts source code into tokens
std::vector<Token> lexer(const std::string& code) {
    std::vector<Token> tokens;
    std::string remainingCode = code;
    while (!remainingCode.empty()) {
        remainingCode = std::string(remainingCode.begin(), std::find_if(remainingCode.begin(), remainingCode.end(), ::isspace));

        bool matched = false;
        for (const auto& entry : patterns) {
            TokenType type = entry.first;
            const std::regex& pattern = entry.second;
            std::smatch match;
            if (std::regex_search(remainingCode, match, pattern)) {
                tokens.push_back(Token{type, match.str()});
                remainingCode = remainingCode.substr(match.length());
                matched = true;
                break;
            }
        }
        if (!matched) {
            throw std::runtime_error("Unexpected token: " + remainingCode.substr(0, 10));
        }
    }
    return tokens;
}

// Abstract Syntax Tree (AST) node
class Node {
public:
    std::string type;
    std::string value;
    std::vector<std::shared_ptr<Node>> children;

    Node(std::string t, std::string v = "") : type(std::move(t)), value(std::move(v)) {}
};

// Parser: Builds AST from tokens
std::shared_ptr<Node> parse(std::vector<Token>& tokens) {
    if (tokens.empty()) return nullptr;

    Token token = tokens.front();
    tokens.erase(tokens.begin());

    if (token.type == NUMBER) {
        return std::make_shared<Node>("Number", token.value);
    } else if (token.type == IDENTIFIER) {
        return std::make_shared<Node>("Identifier", token.value);
    } else if (token.type == KEYWORD) {
        return std::make_shared<Node>("Keyword", token.value);
    } else if (token.type == STRING) {
        return std::make_shared<Node>("String", token.value);
    }

    throw std::runtime_error("Unexpected token: " + token.value);
}

// Conversion table from DIP-LANG syntax to target representation
std::map<std::string, std::string> conversionTable = {
    {"var", "DECLARE"},
    {"func", "DEFINE_FUNCTION"},
    {"return", "RETURN_VALUE"},
    {"if", "IF_CONDITION"},
    {"else", "ELSE_BLOCK"},
    {"while", "WHILE_LOOP"},
    {"struct", "DEFINE_STRUCT"},
    {"import", "IMPORT_MODULE"},
    {"export", "EXPORT_SYMBOL"},
    {"class", "DEFINE_CLASS"},
    {"for", "FOR_LOOP"},
    {"break", "BREAK_STATEMENT"},
    {"continue", "CONTINUE_STATEMENT"}
};

// Code Generation using ConversionTable.txt mappings
std::string codegen(std::shared_ptr<Node> ast) {
    if (ast->type == "Number") {
        return ast->value;
    } else if (ast->type == "Identifier") {
        return ast->value;
    } else if (ast->type == "Keyword") {
        auto it = conversionTable.find(ast->value);
        if (it != conversionTable.end()) {
            return it->second;
        } else {
            return ast->value;
        }
    } else if (ast->type == "String") {
        return "\"" + ast->value + "\"";
    } else if (ast->type == "Expression") {
        std::string result;
        for (const auto& child : ast->children) {
            result += codegen(child) + " ";
        }
        return result;
    }
    return "";
}

// Compiler entry point
std::string compile_code(const std::string& source) {
    auto tokens = lexer(source);
    auto ast = parse(tokens);
    return codegen(ast);
}

// Example usage
int main() {
    std::string sourceCode = "class MyClass { var x = 10; func getX() { return x; } }";
    try {
        std::string compiledOutput = compile_code(sourceCode);
        std::cout << "Compiled Output: " << compiledOutput << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Compilation Error: " << e.what() << std::endl;
    }
    return 0;
}
