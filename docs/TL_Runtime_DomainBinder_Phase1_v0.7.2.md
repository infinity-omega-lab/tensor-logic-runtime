# Tensor Logic Runtime v0.7.x
## Phase 1 Domain Binding Design (Reference Runtime)

### Status
- Applies to: TL Runtime v0.7.2 (frozen correctness baseline)
- Scope: Phase 1 only (execution-mapping verification)
- This document is **normative for the reference runtime**, not an optimization spec.

---

## 1. Purpose

This document defines the **minimal and deterministic rules** for binding index domains
(e.g. `k` in `A[*k] = B[k]`) during **Phase 1 runtime execution**.

The goal is **not** to generalize iteration semantics, but to:
- Verify that *reduce semantics* are correctly mapped into execution
- Preserve determinism and explicit failure behavior
- Avoid introducing future constraints or hidden semantics

---

## 2. Architectural Position

Domain binding is performed **after IR generation and before execution**,
inside a dedicated bridge-layer component:

```
IR (canonical)
  ↓
DomainBinder (Phase 1)
  ↓
IndexDomainRegistry (0..N-1 enumeration)
  ↓
ReduceExecutor (reference runtime)
```

Key constraints:
- ReduceExecutor **does not know** where domains originate
- IndexDomainRegistry **does not infer meaning or shape**
- DomainBinder is the **only component** allowed to decide domain size

---

## 3. Reduce Target Identification (Precondition)

Domain binding applies **only** to IR nodes explicitly marked as reduce operations.

### 3.1 Reduce Identification Signal

A node is a reduce target **iff**:
- `IRNode.kind == IR_Reduce`

This signal is introduced during AST → IR lowering and is explicit.

### 3.2 Reduce Variables

- Reduce variables (e.g. `k` from `*k`) are stored explicitly as:
  - `IR_Reduce.reduce_vars: List<IndexVar>`
- Variables are lexically normalized prior to binding

---

## 4. Phase 1 Domain Binding Rules

### Rule D1 — Domain Source

For each index variable `v`:
- Collect all tensor access occurrences where `v` appears as an axis index
- Extract the axis size from the corresponding tensor shape

### Rule D2 — Consistency Requirement

- If multiple occurrences exist:
  - All axis sizes **must be identical**
  - Otherwise, binding fails with a runtime error

### Rule D3 — Reduce vs Non-Reduce Variables

- Reduce (`*k`) and non-reduce (`k`) variables share the same domain semantics
- Reduction affects **aggregation behavior only**, not domain enumeration

### Rule D4 — Enumeration

- Once size `N` is determined, the domain is registered as:
  - `{0, 1, ..., N-1}`
- Enumeration order and normalization are delegated to `IndexDomainRegistry`

---

## 5. Minimal Example (v0.7.2 Baseline)

```tl
A[*k] = B[k]
```

Binding result:
- `k` appears only in `B[k]`
- Domain size `N` is taken from `B.shape[k_axis]`
- Registered domain: `{0..N-1}`

This is a **special case of Rule D1**, not an exception.

---

## 6. Error Handling Policy

Domain binding must fail explicitly if:
- No tensor occurrence provides a domain size
- Conflicting axis sizes are observed
- A reduce operator is unsupported by the reference runtime (e.g. `AvgSet`)

Silent fallback or inference is **not permitted**.

---

## 7. Non-Goals (Phase 1)

The following are intentionally excluded:
- Shape inference or broadcasting
- External or declared domains
- Pragma-based domain modification
- Parallel execution strategies

---

## 8. Forward Compatibility Notes (Non-Normative)

Future versions may extend DomainBinder to support:
- Explicit domain declarations
- External iterators or datasets
- Pragma-provided execution hints

Such extensions must:
- Not modify reduce semantics
- Not require changes to ReduceExecutor
- Remain isolated within DomainBinder

---

## 9. Summary

Phase 1 domain binding:
- Is minimal, deterministic, and explicit
- Introduces no hidden semantics
- Preserves extensibility by design

This design forms a **correctness anchor** for all future runtime evolution.
