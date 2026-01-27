# jsonpath-cpp
A JSONPath query engine in C++ with a strongly-typed AST and runtime evaluator.

## Overview
jsonpath-engine is a C++ implementation of the JSONPath query language.
It parses JSONPath expressions into a strongly-typed abstract syntax tree (AST) and evaluates them against JSON documents to produce query results.

The project is designed with a clear separation between parsing, semantic representation, and execution, mirroring the architecture of language runtimes and interpreters.

## Features
- JSONPath grammar implemented in modern C++
- Strongly-typed AST with explicit node semantics
- AST-driven query execution model
- Deterministic, side-effect-free evaluation
- Header-only parsing layer
- Clear separation of parse-time and run-time concerns

## Architecture
- The implementation is split into three logical phases:

#### 1. Parsing
Transforms a JSONPath expression into an AST.

#### 2. Semantic Representation (AST)
Each AST node represents a distinct JSONPath operation (root, property access, indexing, filters, etc.).

#### 3. Execution
The AST is walked against a JSON document to produce a result set.

This structure enables:
- straightforward extension of the language
- isolated testing of grammar vs execution
- predictable evaluation behavior

## Parsing Strategy
The parser is implemented using Boost.Spirit X3, allowing the grammar to be expressed directly in C++ and producing a strongly-typed AST without a separate lexer or code-generation step.

Attribute propagation is used to construct AST nodes directly from grammar rules, eliminating intermediate parse representations.

## Execution Model
JSONPath expressions are executed by walking the AST against an input JSON document.

Execution is:
- context-aware
- non-mutating
- driven by explicit node semantics rather than string interpretation

Each AST node defines how it transforms an input JSON context into an output set.

## JSON Backend
The runtime operates on nlohmann::json values, providing:

- a familiar, standards-compliant JSON data model
- predictable value semantics
- easy interoperability with existing C++ code

The JSON backend is abstracted to allow replacement if needed.

### Example
```
#include "jsonpath/engine.hpp"

nlohmann::json doc = R"({
  "store": {
    "book": [
      { "category": "reference", "price": 8.95 },
      { "category": "fiction",   "price": 12.99 }
    ]
  }
})"_json;

auto result = jsonpath::evaluate("$.store.book[*].price", doc);
```

## Build
### Requirements
- C++17 or later
- CMake
- Boost (Spirit X3)
- nlohmann/json (https://github.com/nlohmann/json)

### Build Steps
```
cmake -S . -B build
cmake --build build
```

## Project Status
The project is under active development.

Planned work includes:
- implement all selector types [listed here](https://www.rfc-editor.org/rfc/rfc9535.html#name-selectors-2)
- filter expressions
- full JSONPath compliance (eventually)
- performance optimizations
- test coverage

## Design Notes
This project was originally prototyped using Flex/Bison and later reimplemented using Boost.Spirit X3 to improve type safety, reduce boilerplate, and enable direct AST construction from the grammar.

## License
MIT

