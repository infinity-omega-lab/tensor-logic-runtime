# Tensor Logic Runtime v0.7 — Initial Compiler (Mode B)

This project provides the first-cut C++17 implementation of the Tensor Logic Runtime v0.7 compiler pipeline. It is scoped to Mode B: a fully wired parser → AST → IR → runtime skeleton, with algorithmic internals stubbed and clearly marked `TODO` per the diagrams and TOC.

## Layout
- `include/` — Public headers (parser, AST, IR, runtime entrypoints).
- `src/parser/` — Lexer and recursive-descent parser derived from `tld_core_grammar_v0.1.bnf`.
- `src/ir/` — Minimal IR nodes and builder bridging AST to runtime.
- `src/runtime/` — Runtime skeleton wiring PCL → SMM → TIL → GDA → AOL → DRA → UCG → RDE (see `tl_runtime_v0_7_overview.md` and diagram registry).
- `src/main.cpp` — Demo entrypoint: parse input, build IR, execute no-op runtime pipeline.
- `tests/` — Smoke tests that parse a snippet, build IR, and run the pipeline without crashing.

## Building
```bash
cmake -S A_oss_public/compiler/tl_runtime_v0_7_cpp -B build/tl_runtime_v0_7_cpp
cmake --build build/tl_runtime_v0_7_cpp
```

### Running the demo
```bash
./build/tl_runtime_v0_7_cpp/tl_runtime_v0_7_demo
```
The demo parses a hard-coded Tensor Logic snippet, constructs the IR, and executes the wired runtime pipeline as a no-op pass-through.

### Tests
Tests are enabled by default:
```bash
ctest --test-dir build/tl_runtime_v0_7_cpp
```

## References
- Grammar: `A_oss_public/spec/tld_core_grammar_v0.1.bnf`.
- Diagrams: `A_oss_public/docs/Diagram/Codex/` (see registry `A_oss_public/docs/registry/tld_diagram_registry_v0.7.json`).
- TOC: `A_oss_public/docs/tld_master_toc_v0.7.md`.
