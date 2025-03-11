use std::collections::HashMap;
use std::fs;

// Define Token Structure
#[derive(Debug, Clone)]
enum Token {
    Define(String, String, String), // define [type] name = value;
    Compute(String, String, String), // compute var = expr;
    Output(String), // output var;
    MapDiagram(Vec<(String, String)>), // node: "name" -> instruction;
    AsyncTask(String, Vec<String>), // async task name: instructions;
    AwaitTask(String), // await task;
    TryBlock(Vec<String>), // try block for deferred errors
    MemPacketize(String, Vec<String>), // mem.packetize [type] dataset;
    MemStream(String, String), // mem.stream dataset to RAM;
    CompileAOT, // compile AOT -> HEX -> BIN;
    RenderOptimize, // render.optimize with [multi-thread, boolean-logic];
    Await7FSEN(String), // await 7FSEN event;
}

// Lexer: Tokenize DIP-Lang Syntax
fn lexer(input: &str) -> Vec<Token> {
    let mut tokens = Vec::new();
    for line in input.lines() {
        let parts: Vec<&str> = line.trim().split_whitespace().collect();
        if parts.is_empty() { continue; }
        match parts[0] {
            "define" => tokens.push(Token::Define(parts[1].to_string(), parts[2].to_string(), parts[4].to_string())),
            "compute" => tokens.push(Token::Compute(parts[1].to_string(), parts[2].to_string(), parts[4].to_string())),
            "output" => tokens.push(Token::Output(parts[1].to_string())),
            "map-diagram" => {
                let mut nodes = Vec::new();
                for i in 1..parts.len() {
                    let node_parts: Vec<&str> = parts[i].split("->").collect();
                    if node_parts.len() == 2 {
                        nodes.push((node_parts[0].trim().to_string(), node_parts[1].trim().to_string()));
                    }
                }
                tokens.push(Token::MapDiagram(nodes));
            }
            "async" => tokens.push(Token::AsyncTask(parts[2].to_string(), vec![parts[4].to_string()])),
            "await" => tokens.push(Token::AwaitTask(parts[1].to_string())),
            "try" => tokens.push(Token::TryBlock(vec![parts[2].to_string()])),
            "mem.packetize" => tokens.push(Token::MemPacketize(parts[1].to_string(), vec![parts[3].to_string()])),
            "mem.stream" => tokens.push(Token::MemStream(parts[1].to_string(), parts[3].to_string())),
            "compile" => tokens.push(Token::CompileAOT),
            "render.optimize" => tokens.push(Token::RenderOptimize),
            "await" if parts[1] == "7FSEN" => tokens.push(Token::Await7FSEN(parts[2].to_string())),
            _ => {}
        }
    }
    tokens
}

// Parser: Convert Tokens into Execution Tree
fn parser(tokens: Vec<Token>) {
    for token in tokens {
        match token {
            Token::Define(dtype, name, value) => println!("Defining variable {} of type {} with value {}", name, dtype, value),
            Token::Compute(var, op, val) => println!("Computing {} = {} {}", var, op, val),
            Token::Output(var) => println!("Outputting value of {}", var),
            Token::MapDiagram(nodes) => println!("Mapping diagram: {:?}", nodes),
            Token::AsyncTask(name, instructions) => println!("Asynchronous Task: {} -> {:?}", name, instructions),
            Token::AwaitTask(name) => println!("Awaiting Task: {}", name),
            Token::TryBlock(errors) => println!("Deferring Errors: {:?}", errors),
            Token::MemPacketize(dtype, dataset) => println!("Packetizing Memory: {:?} of type {}", dataset, dtype),
            Token::MemStream(dataset, destination) => println!("Streaming {} to {}", dataset, destination),
            Token::CompileAOT => println!("Compiling AOT to HEX and then to BIN"),
            Token::RenderOptimize => println!("Optimizing Rendering with Multi-threaded Boolean Logic"),
            Token::Await7FSEN(event) => println!("Handling 7FSEN Event: {}", event),
        }
    }
}

fn main() {
    let code = fs::read_to_string("dip_example.dip").expect("Failed to read file");
    let tokens = lexer(&code);
    parser(tokens);
}
