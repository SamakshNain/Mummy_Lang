<!-- # Mummy_Lang
Mini compiler project implementing a custom Hindi-inspired language “Mummy” using Lex and Yacc. Supports variable declarations, arithmetic expressions, input/output, conditionals, loops, and nested blocks with an end keyword. Demonstrates lexical analysis, CFG design, and bottom-up parsing in compiler construction. -->
# Mummy_Lang

Mummy_Lang is a mini compiler project that implements a custom Hindi-inspired programming language called **Mummy** using **Lex and Yacc**.

The project demonstrates important compiler design concepts such as lexical analysis, context-free grammar design, bottom-up parsing, and syntax validation. It supports basic programming features like variable declarations, arithmetic expressions, input/output statements, conditionals, loops, and nested blocks using an `end` keyword.

## Features

- Custom Hindi-inspired language syntax
- Lexical analysis using Lex
- Parser generation using Yacc
- Variable declaration support
- Arithmetic expression evaluation
- Input and output statements
- Conditional statements
- Looping constructs
- Nested block handling
- Syntax error detection

## Tech Stack

- C
- Lex
- Yacc
- GCC

## Project Files

```text
Mummy_Lang/
│── mummy.l        # Lex file for token generation
│── mummy.y        # Yacc file for grammar rules and parsing
│── mummy.tab.c    # Generated parser source file
│── mummy.tab.h    # Generated parser header file
│── README.md
