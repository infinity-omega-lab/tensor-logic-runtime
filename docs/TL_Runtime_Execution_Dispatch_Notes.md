# TL Runtime Execution Dispatch — Normative Notes

This document defines **normative constraints** for execution dispatch
in Tensor Logic Runtime.

It does not describe future capabilities, alternatives, or design intent.
Only constraints that are **binding** for v1.0-draft and v1.1-alpha are listed.

---

## Normative Constraints

1. **Single Execution Path**

   All runtime execution dispatch is fixed to `ReduceExecutor`.

   No alternative executor selection is permitted at runtime.

2. **No Runtime Switching**

   Execution dispatch must not vary based on:
   - configuration
   - inference
   - heuristics
   - data-dependent conditions

3. **Unreachable Alternatives**

   Any alternative executor concepts
   (including but not limited to `Avg`, `Max`, or multi-dispatch)
   are unreachable and non-operational
   in v1.0-draft and v1.1-alpha.

4. **Semantic Preservation**

   Execution dispatch must not alter:
   - existing semantics
   - execution boundaries
   - reduction behavior defined prior to v1.0-draft

---

## Scope

These constraints are binding for:
- v1.0-draft
- v1.1-alpha

Any future exploration of execution dispatch
is explicitly out of scope for this document.
