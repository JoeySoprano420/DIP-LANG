use std::collections::VecDeque;

#[derive(Debug, Clone)]
pub enum ASTNode {
    Definition(String, f64), // Represents variable definitions
    Output(String),          // Represents output statements
}

pub struct Parser {
    tokens: VecDeque<Token>,
}

impl Parser {
    pub fn new(tokens: Vec<Token>) -> Self {
        Self {
            tokens: VecDeque::from(tokens),
        }
    }

    pub fn parse(&mut self) -> Vec<ASTNode> {
        let mut ast = Vec::new();
        while let Some(token) = self.tokens.pop_front() {
            match token.token_type {
                TokenType::Define => {
                    if let Some(TokenType::Identifier(name)) = self.tokens.pop_front().map(|t| t.token_type) {
                        if let Some(TokenType::Operator(_)) = self.tokens.pop_front().map(|t| t.token_type) {
                            if let Some(TokenType::Number(value)) = self.tokens.pop_front().map(|t| t.token_type) {
                                ast.push(ASTNode::Definition(name, value));
                            }
                        }
                    }
                }
                TokenType::Output => {
                    if let Some(TokenType::Identifier(name)) = self.tokens.pop_front().map(|t| t.token_type) {
                        ast.push(ASTNode::Output(name));
                    }
                }
                _ => {
                    // Ignore unexpected tokens
                }
            }
        }
        ast
    }
}
