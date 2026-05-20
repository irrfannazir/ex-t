# Lexical Analyzer (Lexer) using Deterministic Finite Automata (DFA)

This module is a C-based Lexical Analyzer designed to scan source code strings or external files and partition them into distinct lexical tokens based on a state-machine implementation. It maps characters to language-defined categories while tracking contextual details like indentation levels and inline grouping symbols.

---

## Architecture Overview

The program tokenizes input characters step-by-step using an internal Deterministic Finite Automaton (DFA) model. It processes either explicit terminal scripts via standard input or dedicated source files, managing intermediate token state configurations across files before compiling them into a final structured formatting scheme.

### Key Features
*   **DFA-Driven Scanning:** Transitions cleanly between operational modes (states) for identifiers, operators, digits, and strings.
*   **Indentation Tracking:** Dynamically counts and registers indentation constraints (e.g., Pythonic scoped formatting).
*   **Contextual Overrides:** Detects structural groupings (`{`, `(`, `}`, `)`) to seamlessly pass over non-syntactic line-breaks (`ignore_newline`).
*   **Robust Error Logging:** Implements localized structural and syntax diagnostics (e.g., flags illegal variable descriptors originating with digits).

---

## State Machine Breakdown

The lexer functions via explicit state evaluations wrapped within `dfa_char_analysis`. The mapping rules are defined as follows:

| State | Role | Input Behavior & Next State Transition |
| :--- | :--- | :--- |
| **Case 0** | **Start State (Post-Newline)** | Tracks character indentation offsets. Directs structural groupings to strings, identifiers, numbers, operators, or punctuations. |
| **Case 1** | **Whitespace Detection** | Tracks multiple sequential spacing instances. Resets line configurations when newlines or raw `;` delimiters are parsed. |
| **Case 2** | **String Litteral Processing** | Captures sequential elements between active string qualifiers (`TOKEN_STRING`), returning safely to Case 0 on completion. |
| **Case 3** | **Identifier Detection** | Tracks typical multi-character variables/keywords. Hands off tracking to punctuation or operators dynamically if encountered. |
| **Case 4** | **Numerical Constants** | Maps legal digits (`TOKEN_INTEGER`). Evaluates and logs lexical faults if standard text fields attempt to merge into a base digit block. |
| **Case 5** | **Operators Evaluation** | Gathers character-based logical or mathematical operators (`TOKEN_OPERATOR`). |
| **Case 6** | **Punctuation Isolation** | Captures distinct operational syntax characters safely and marks terminal boundaries (`TOKEN_PUNCTUATION`). |
| **Case -1**| **Terminated Execution** | Halts current file scan loops on encountering fatal layout criteria. |

---

## Principal Functions

### `int dfa_char_analysis(char c, int *s, struct lexInfo *li)`
Core character analysis routine executing the state machine operations. 
*   **`c`**: Target scanning byte element.
*   **`s`**: Reference pointer capturing the core operational State.
*   **`li`**: Struct tracking global contextual state structures (`indent`, `ignore_newline`).

### `int lexf(const int8_t isinput, const char *ex_filename, const char *dest_filename)`
Top-level controller function handling setup, execution, and cleanup hooks for the tokenization lifecycle.
*   Initializes tracking variables and flushes temporary output pipelines (`DFA_LEXEME_FILENAME`, `DFA_TOKEN_FILENAME`).
*   Directs scanning operations sequentially via dynamic stdin buffering (`isinput = 1`) or internal `fopen` system streams (`isinput = 0`).
*   Executes terminal block-line checks and aggregates standard lexical components using `change_to_form` before wiping active staging tracks.

---

## File Dependencies & Dependencies

The module requires custom operational dependencies referenced across localized source headers:
```c
#include "lex/lexh.h"             // Main structural signatures
#include "lex/lfh.h"              // System file stream interfaces 
#include "lex/lexInfo.h"          // Tracking layout definitions
#include "lex/dfah.h"             // System DFA functions and constants
#include "lex/lfn.h"              // Filenames
#include "lex/d_fh.h"             // Output serialization routines
#include "lex/lerror.h"           // Core lexical evaluation alerts
#include "common/constants.h"     // Shared constants
#include "common/pc_error.h"      // Panic compilation handlers