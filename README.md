# Tensor Logic Runtime — v0.7 Public Preview

Tensor Logic is a runtime and cognitive-structure design **inspired by and
developed upon the conceptual foundations presented in the following research**:

**Original Paper:**  
“Tensor Logic: The Language of AI” 
Pedro Domingos
https://arxiv.org/abs/2510.12269

We express our appreciation to the authors of the above work.  
The Tensor Logic runtime presented here is an independent engineering project,
but its conceptual direction and design motivation were informed by the ideas
explored in that research.

Tensor Logic (TL) is a **deterministic cognitive runtime** designed to model
coherent reasoning processes through a reproducible, interpretable state
architecture. It is **not** a deep learning framework, nor an inference engine,
nor a replacement for existing model architectures.

Instead, TL provides a **unified cognitive substrate** that can host
model-agnostic reasoning flows with strict internal consistency.

This repository contains the **public v0.7 draft**, including:
- the architecture overview,
- the Persona Layer specification,
- the minimal C++17 runtime scaffold,
- and the grammar used for the initial parser prototype.

### What’s New in v0.7

This public preview introduces:
- the full deterministic layer set (UCG / SMM / TIL / DRA / AOL / GDA),
- cross-host canonical equivalence rules,
- semantic sealing boundaries via SMM-v2,
- Profile Architecture v2 (independent specification),
- CVCL v2 (Cross-Version Compatibility Layer),
- the public Persona Layer (Section 12.4),
- the unified diagram set for v0.7,
- and deterministic merging rules validated via L1/L2 dry-run success.

v0.7 is the first version that forms a **closed deterministic runtime model**
with consistent semantics, prediction, identity, and distributed behavior.

### TL Runtime v0.7.2
- Reference ReduceExecutor finalized
- avg= is explicitly unsupported in the v0.7.x reference runtime to avoid undefined semantics
- Deterministic reduce execution verified by minimal correctness test

### Reference Runtime Phase 1 (v0.7.2)

Version v0.7.2 finalizes the **Phase 1 reference execution path** for reduce semantics.
- Deterministic reduce execution verified by `tl_runtime_v0_7_reduce_test.exe`
- Deterministic single-threaded ReduceExecutor
- Explicit domain binding via DomainBinder
- Unsupported operations (e.g. AvgSet) fail explicitly
- No implicit allocation, inference, or optimization

Reference documents:
- `TL_Runtime_Phase1_Minimal_Execution_Flow_v0.7.2.md`
- `TL_Runtime_DomainBinder_Phase1_v0.7.2.md`

This phase serves as the frozen correctness baseline for all future runtime phases.

---

## What This Project Is Not

To avoid misunderstanding:

- TL is **not** a competitor to PyTorch, TensorFlow, JAX, or any ML framework.
- TL is **not** a conventional inference engine.
- TL is **not** a philosophical manifesto disguised as software.

TL focuses on **structured cognition**,  
not on training, optimizing, or replacing neural networks.

It introduces a substrate on which **deterministic,
interpretable, and self-consistent reasoning systems** can be built.

---

## What’s Included in v0.7 (Public Preview)

### 1. Architecture Overview (Diagram Set)
A visual representation of the TL cognitive structure, including:
- Unified Canonical Graph (UCG)
- Predictive Convergence Layer (PCL)
- PCC1 / PCC2 loops
- Replay Gate
- Drift and Hazard interfaces

These diagrams provide a structural foundation for understanding the TL model.

### 2. Persona Layer — Public Specification
A formal description of TL’s identity semantics:
- Stable Persona (SSIG)
- Modulated Persona (MSIG)
- Dynamic Persona (DSIG)
- Alignment and safety boundaries

This layer defines how a reasoning system maintains **linguistic identity**
and **context continuity** across long sequences.

The Persona Layer operates outside the runtime core and, together with Profile Architecture v2, defines the stable identity boundary for cross-version cognitive continuity.

### 3. Runtime Scaffold (C++17)

This repository provides a **minimal but functional C++17 runtime scaffold** for Tensor Logic, including:

- Lexer (tokenization)
- Recursive-descent parser
- Direct AST construction
- AST → IR lowering (minimal implementation)
- Smoke tests validating the grammar → AST → IR pipeline

The implementation is intentionally lightweight and dependency-free, serving as a **clear baseline** for researchers and implementers who wish to extend or replace individual layers.

---

## Repository Structure

```
tl_runtime_v0_7_cpp/
├── CMakeLists.txt
├── README.md
├── include/
│   └── tl/
│       ├── ast/        # AST node definitions
│       ├── ir/         # IR structures and builder
│       ├── parser/     # Lexer, parser, tokens
│       └── runtime/    # Execution/runtime stubs
├── src/
│   ├── main.cpp        # Demo / smoke execution
│   ├── ir/
│   ├── parser/
│   └── runtime/
└── tests/
    └── parser_runtime_smoke.cpp
```

---

## Build Instructions

### Requirements
- CMake 3.15 or newer
- A C++17 compatible compiler  
  (tested with MSVC; Clang and GCC should also work)

### Build (out-of-source)

From the `tl_runtime_v0_7_cpp` directory:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

### Run demo

```sh
./tl_runtime_v0_7_demo
```

This will execute a no-op demo pipeline that validates parsing and IR construction.
- v0.7.1: IR builder structural sanity check completed.

### Run Tests

ctest

### Roadmap
#### v0.8 — Implementation Phase
    expanded runtime functions
    TL tensor converter (Python → TL)
    initial cognitive shell draft
    hands-on documentation

#### v1.0 — Full Cognitive Release
    stable APIs
    extended reasoning modules
    integration guides
    formal runtime specification

### Contribution
For questions, suggestions, or issues,
please use the GitHub issue tracker in this repository.
No direct contact or research collaboration channels are provided at this stage.

### License
Tensor Logic Runtime (OSS Edition) is released under the Apache License 2.0.
Commercial use, integration into proprietary systems, or deployment at scale
requires a separate commercial license (TLCL).

Consequently:

- **Commercial use of the public subset is permitted** under Apache-2.0.  
- **Commercial use of the full Tensor Logic system is not granted**, and requires
a separate commercial agreement under the Tensor Logic Core License (TLCL).

The separation ensures that open research remains unrestricted,  
while advanced system components retain their intended licensing model.
