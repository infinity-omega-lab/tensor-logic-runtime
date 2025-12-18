# Reference IndexDomainRegistry Design (TL Runtime v0.7.1)

## Purpose
IndexDomainRegistry is the **single source of determinism** for index traversal
in the reference interpreter.

It provides finite, ordered integer domains for index variables without
embedding any semantic logic.

## Design Principles
- Determinism over flexibility
- Finite integer domains only (v0.7.x)
- No semantic knowledge (reduce / pragma unaware)
- Simple, inspectable implementation

## Responsibilities
- Register domain sizes for index variables
- Enumerate domain values in a fixed, deterministic order (0..N-1)
- Normalize reduction variable lists via lexicographic ordering

## Non-Goals
- No dynamic resizing
- No shape inference
- No caching or optimization
- No virtual / overwrite semantics

## API Summary
- set_domain_size(var, size)
- domain_size(var) -> size
- enumerate(var) -> vector<IndexValue>
- sort_lex(vars) -> normalized vars

## Rationale
Deterministic traversal is essential for reproducible reduce semantics.
This component intentionally restricts expressiveness to guarantee stability.

Optimized runtimes may replace this registry entirely, provided that
observable traversal order remains identical.
