# Tiny Expression Compiler (Lexer + Parser)

## Overview

This project is a minimal compiler front-end written in C++ that demonstrates the core stages of parsing arithmetic expressions:

1. **Lexical Analysis (Lexer)** – Converts raw source code into tokens
2. **Parsing (Recursive Descent Parser)** – Builds an Abstract Syntax Tree (AST) from tokens

It supports a simple expression language with:

* Numbers (integers and floats)
* Identifiers (variable names)
* Addition (`+`)
* Multiplication (`*`)
* Parentheses (`(...)`)

The goal of this project is to provide a clear, educational implementation of how compilers process expressions.

---

## Features

* Tokenization with line/column tracking
* Support for identifiers and floating-point numbers
* Recursive descent parser
* Operator precedence handling (`*` > `+`)
* AST construction using `std::unique_ptr`
* AST pretty-printing for visualization
* Basic error handling for:

  * Invalid characters (lexer)
  * Unexpected tokens (parser)

---

## Grammar

The parser implements the following grammar:

```
Expression   -> Term (+ Term)*
Term         -> Factor (* Factor)*
Factor       -> NUMBER | IDENTIFIER | (Expression)
```

This ensures correct operator precedence:

* Multiplication binds tighter than addition
* Parentheses override precedence

---

## Project Structure

```
.
├── lexer.h        # Token definitions and Lexer interface
├── lexer.cpp      # Lexer implementation
├── parser.h       # AST node definitions and Parser interface
├── parser.cpp     # Parser implementation
```

---

## Lexer

The lexer reads a string input and produces a sequence of tokens.

### Token Types

* `NUMBER` – e.g. `42`, `3.14`
* `IDENTIFIER` – e.g. `x`, `input_A`
* `PLUS` – `+`
* `STAR` – `*`
* `LPAREN` – `(`
* `RPAREN` – `)`
* `END_OF_FILE` – EOF marker
* `UNKNOWN` – invalid/unrecognized characters

### Example

Input:

```
a + 3 * (b + 2)
```

Output tokens:

```
[IDENTIFIER: a] [PLUS: +] [NUMBER: 3] [STAR: *] ...
```

---

## Parser

The parser uses **recursive descent** to convert tokens into an AST.

### AST Node Types

* **NumNode** → numeric literals
* **IdNode** → identifiers
* **BinOpNode** → binary operations (`+`, `*`)

### Example AST

For input:

```
a + 3 * b
```

The AST looks like:

```
[Binary OP: +]
  [Identifier: a]
  [Binary OP: *]
    [Number: 3]
    [Identifier: b]
```


---

## Error Handling

### Lexer Errors

* Prints a message for unknown characters:

```
Lexical Error: Unrecognized character '@' at Line X, Col Y
```

### Parser Errors

* Throws `std::runtime_error` for unexpected tokens:

```
Unexpected token at line X column Y
```

---

## Limitations

This is a minimal educational compiler and currently does **not** support:

* Subtraction or division
* Unary operators (e.g. `-x`)
* Assignment or statements
* Type checking
* Code generation or evaluation

---

## Future Improvements

Possible extensions include:

* Add more operators (`-`, `/`)
* Implement unary expressions
* Add variable assignment
* Build an interpreter or evaluator
* Add error recovery instead of throwing exceptions
* Extend grammar (functions, conditionals, etc.)

---

## Build & Run

Compile with a C++17 (or newer) compiler:

```bash
g++ lexer.cpp parser.cpp -o compiler
./compiler
```

*(You’ll need to add your own `main.cpp` to drive execution.)*

---

## Purpose

This project is designed for learning:

* How lexers work
* How recursive descent parsers are implemented
* How ASTs represent program structure

It intentionally keeps things simple and readable rather than fully featured.

---

## License

This project is open for educational use.
