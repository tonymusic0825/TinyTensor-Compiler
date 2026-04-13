# Tiny Tensor Compiler 

A minimal experimental compiler for tensor-style expressions, written in C++.  
This project focuses on building the core components of a compiler from scratch: **lexing**, **parsing**, and **AST construction**.

---

## Features

- **Lexer (Tokenizer)**
  - Converts raw input strings into tokens
  - Supports:
    - Numbers (integers & floats)
    - Identifiers (e.g., `x`, `weights`)
    - Operators (`+`, `*`)
    - Parentheses `(` `)`
  - Tracks line and column for error reporting

- **Parser**
  - Builds an **Abstract Syntax Tree (AST)** from tokens
  - Supports:
    - Binary expressions (`+`, `*`)
    - Identifiers and numeric literals
  - Simple recursive descent parsing

- **AST Representation**
  - Node types:
    - `NumNode` (numeric literals)
    - `IdNode` (identifiers)
    - `BinOpNode` (binary operations)
  - Tree visualization via `print()`

---

## Project Structure
