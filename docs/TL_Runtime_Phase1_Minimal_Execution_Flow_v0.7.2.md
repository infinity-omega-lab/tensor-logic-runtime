# Tensor Logic Runtime v0.7.x
## Phase 1 Minimal Execution Flow (Reference Runtime Integration Check)

### Status
- Applies to: TL Runtime v0.7.2 (frozen correctness baseline)
- Scope: Phase 1 only (single-pass end-to-end mapping verification)
- No new semantics, no optimization, no parallelism

Related document:
- `TL_Runtime_DomainBinder_Phase1_v0.7.2.md` (Domain binding rules and responsibilities)

---

## 1. Purpose

Phase 1 exists to verify that the **spec-level reduce semantics** are correctly mapped into
the **reference runtime execution** path:

```
Parser → AST → IR → DomainBinder → ReducePlan → ReduceExecutor
```

Success means:
- The mapping is structurally correct (no hidden inference)
- Determinism holds (same input → same IR/plan → same output)
- Unsupported operations fail explicitly (reference runtime does not lie)

---

## 2. Core Principles (Non-negotiable)

1. **Single source of truth is the frozen baseline (v0.7.2).**
2. **One bridge only.** Runtime binding happens in a dedicated bridge layer.
3. **Immutability in Phase 1.** AST/IR/RuntimeProgram/ReducePlan are read-only snapshots.
4. **Explicit failure.** If something is not defined, it must fail, not guess.
5. **No “helpful” behavior.** No shape inference, no optimization, no parallelism.

---

## 3. Components and Responsibilities

### 3.1 Parser
- Input: TL source text
- Output: AST
- Responsibility: produce a syntactically valid AST (or fail with parse errors)

### 3.2 AST Validation (Phase 1 minimum)
- Checks only what is required to proceed to IR lowering safely:
  - Reduce syntax nodes exist where expected
  - LHS/RHS are structurally valid tensor references for the baseline test

### 3.3 Lowering (AST → Canonical IR)
- Output: Canonical IR
- Responsibility:
  - Create explicit reduce IR nodes (`IR_Reduce`)
  - Preserve lexical-normalized index variables
- Non-responsibility:
  - No domain binding
  - No runtime strategy selection

### 3.4 DomainBinder (Bridge Layer)
- Input: Canonical IR + TensorStore (for shape access)
- Output: IndexDomainRegistry registrations + DomainBindingResult
- Responsibility:
  - Bind each index variable to a finite domain size `N`
  - Register `{0..N-1}` in IndexDomainRegistry
  - Enforce consistency (conflicts → explicit error)
- Reference: see `TL_Runtime_DomainBinder_Phase1_v0.7.2.md`

### 3.5 ReducePlanBuilder (Bridge Layer)
- Input: Canonical IR + DomainBindingResult + Symbol/Tensor refs
- Output: `ReducePlan[]` (immutable)
- Responsibility:
  - Convert each `IR_Reduce` node into an executable plan entry
  - Carry only execution-relevant fields:
    - op_kind (Sum/Min/Max/AvgSet etc.)
    - lhs_tensor_ref, rhs_tensor_ref
    - reduce_vars, axis mapping
    - domain refs (from IndexDomainRegistry)
    - write_mode (=, +=, etc. if applicable)
  - Reject unsupported ops for reference runtime (e.g., AvgSet → `std::logic_error`)

### 3.6 ReduceExecutor (Reference Runtime)
- Input: ReducePlan[] + TensorViews
- Output: Mutated target tensors (e.g., A)
- Responsibility:
  - Execute plans deterministically, single-threaded
  - No strategy changes, no reordering unless formally specified in v0.7.2

---

## 4. Phase 1 Single-Pass Flow (Step-by-step)

### Step 0 — Prepare Inputs
- Source text for the baseline test:
  ```tl
  A[*k] = B[k]
  ```
- TensorStore seeded with:
  - `B` tensor data + shape
  - `A` tensor allocated (shape must be compatible with output semantics)

### Step 1 — Parse
- `parse(source) → AST`
- Must either:
  - produce AST, or
  - fail with parse diagnostics (no recovery in Phase 1)

### Step 2 — Minimal AST Validate
- Confirm:
  - exactly one statement (baseline)
  - LHS is tensor reference with a reduce-marked index (`*k`)
  - RHS is tensor reference indexed by `k`

### Step 3 — Lower to Canonical IR
- `lower(AST) → IR`
- Confirm:
  - `IR_Reduce` node exists
  - `reduce_vars == [k]` (lex-normalized)

### Step 4 — Domain Binding
- `DomainBinder.bind(IR, TensorStore) → DomainBindingResult`
- For baseline:
  - Bind `k` from the axis size of `B[k]`
  - Register domain `{0..N-1}`

### Step 5 — Build ReducePlan
- `ReducePlanBuilder.build(IR, DomainBindingResult, TensorStore) → plans`
- Enforce:
  - Unsupported ops reject (AvgSet etc.)
  - Shape/domain conflicts reject (explicit)

### Step 6 — Execute
- `ReduceExecutor.execute(plans, TensorStore)`
- Single-thread, deterministic

### Step 7 — Verify (Correctness Anchor)
- Verify the baseline property defined for v0.7.2:
  - expected values of `A` match the semantics of the statement
- This is a correctness check only:
  - no performance metrics
  - no scheduling/optimization validation

### LHS Tensor Allocation Preconditions (Phase 1)

- The left-hand-side (LHS) target tensor **must be allocated or allocatable** before execution.
- Phase 1 **does not define** how allocation is performed.
- The reference runtime **must not** perform implicit shape inference or automatic allocation.
- Allocation strategy (pre-allocation, external provisioning, etc.) is **out of scope** for Phase 1.
- Failure to meet this precondition **must result in explicit execution failure**.

This rule exists solely to ensure that Phase 1 execution
verifies semantic-to-runtime mapping without introducing hidden behavior.

---

## 5. Observability (Allowed Diagnostics)

To preserve Phase 1 focus, logging is restricted to three observation points:

1. **IR produced**
   - optionally emit canonical hash / node count
2. **ReducePlan produced**
   - op_kind / reduce_vars / domain sizes
3. **Execution completed**
   - verification pass/fail + minimal output summary

Anything else is deferred to later phases.

---

## 6. Failure Modes (Must be Explicit)

Phase 1 must hard-fail on:
- Missing or unbindable domain size
- Conflicting domain sizes across occurrences
- Shape/domain mismatch preventing execution
- Unsupported reduce op in reference runtime (AvgSet)
- Any ambiguity that would require inference

No silent fallback is permitted.

---

## 7. Exit Criteria (Phase 1 Complete)

Phase 1 is considered complete when:
- The baseline test passes through the entire pipeline once
- The mapping is traceable and deterministic
- The failure behavior is explicit and consistent

After Phase 1, proceed to Phase 2:
- minimal pragma ↔ runtime connection design (no implementation)

---
