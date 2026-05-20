# Technical Documentation: Syntactic Parser Subsystem

This document provides a technical specification of the implementation details, system architecture, component design, and API reference for the compiler's Syntactic Parser module.

---

## 1. Architectural Overview

The Syntactic Parser is a core subsystem designed to run immediately after the Lexical Analysis phase. It maps flat, sequential token sequences produced by the lexer against formal structural rules (grammar definitions) stored in an external repository (`SYNTAX_DIRECTORY`).

```
               +-------------------+
               |    Token Stream   |
               +---------+---------+
                         |
                         v
               +-------------------+
               |      parsef()     | <---+ Synchronizes tokens & 
               +---------+---------+     | grammar methods
                         |
          +--------------+--------------+
          | Is expression tree needed?  |
          +--------------+--------------+
                         |
               +---------+---------+
          Yes  |                   | No
         +-----v-----+       +-----v-----+
         | Parse AST |       | Match Raw |
         +-----+-----+       +-----------+
               |
               v
+-----------------------------+
| Output: Dest File & Symbols |
+-----------------------------+

```

The architecture employs a **Hybrid Top-Down Pattern-Matching Parser**. Instead of hardcoding concrete syntax productions into C function cascades, the engine loops dynamically over target template patterns. This allows grammar modifications to be handled directly through file-system configurations rather than forcing a full re-compilation of the compiler binary.

---

## 2. Abstract Syntax Tree (AST) Generation Logic

When the parser handles words requiring expressions or structural operations (`does_tree_needed`), it delegates control to the syntax tree mutations pipeline.

### Tree Node Splitting & Mutation Matrix

The tree generation engine maps complex operators using structural pointer rules:

#### Binary Expression Mutations (`handle_binary_op`)

Splits flat parameters into an isolated expression subtree containing left-hand parameters and an attached right-hand binary expression component.

```
       [Node (ptr)]
       /          \
  Left (Op)      Right (Binary Expression)
                 /                      \
         Right->Right (Operand)    Right->Left (Operand)

```

#### Tertiary Expression Mutations (`handle_tertiary_op`)

Splices complex multi-stage statements (such as conditional constraints or inline branches) across cascading right-hand operational nodes.