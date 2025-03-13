import re
import sys

# Token types based on DIP-LANG syntax
TOKEN_MAP = {
    "KEYWORD": r"\b(if|else|while|return|func|var|struct|import|export)\b",
    "IDENTIFIER": r"\b[a-zA-Z_][a-zA-Z0-9_]*\b",
    "NUMBER": r"\b\d+(\.\d+)?\b",
    "OPERATOR": r"[+\-*/=<>!&|]",
    "SYMBOL": r"[(){},;\[\]]",
    "STRING": r'".*?"'
}

# Lexer: Converts source code into tokens
def lexer(code):
    tokens = []
    while code:
        code = code.lstrip()
        match = None
        for token_type, pattern in TOKEN_MAP.items():
            regex = re.compile(pattern)
            match = regex.match(code)
            if match:
                tokens.append((token_type, match.group(0)))
                code = code[match.end():]
                break
        if not match:
            raise SyntaxError(f"Unexpected token: {code[:10]}")
    return tokens

# Abstract Syntax Tree (AST) node
class Node:
    def __init__(self, type, value=None, children=None):
        self.type = type
        self.value = value
        self.children = children or []

    def __repr__(self):
        return f"Node({self.type}, {self.value}, {self.children})"

# Parser: Builds AST from tokens
def parse(tokens):
    if not tokens:
        return None
    token = tokens.pop(0)
    if token[0] == "NUMBER":
        return Node("Number", token[1])
    elif token[0] == "IDENTIFIER":
        return Node("Identifier", token[1])
    elif token[0] == "KEYWORD":
        return Node("Keyword", token[1])
    elif token[0] == "STRING":
        return Node("String", token[1])
    raise SyntaxError(f"Unexpected token: {token}")

# Code Generation using ConversionTable.txt mappings
def codegen(ast):
    if ast.type == "Number":
        return ast.value
    elif ast.type == "Identifier":
        return ast.value
    elif ast.type == "Keyword":
        conversion_table = {
            "var": "DECLARE",
            "func": "DEFINE_FUNCTION",
            "return": "RETURN_VALUE",
            "if": "IF_CONDITION",
            "else": "ELSE_BLOCK"
        }
        return conversion_table.get(ast.value, ast.value)
    elif ast.type == "String":
        return f'"{ast.value}"'
    return ""  # Expand later with full conversion mappings

# Compiler entry point
def compile_code(source):
    tokens = lexer(source)
    ast = parse(tokens)
    output = codegen(ast)
    return output

# Example usage
if __name__ == "__main__":
    source_code = "var x = 5"
    compiled_output = compile_code(source_code)
    print("Compiled Output:", compiled_output)
