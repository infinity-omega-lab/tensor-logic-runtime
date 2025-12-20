# Post-Phase 2 Work Overview
**Tensor Logic Runtime — Roadmap After Phase 2 (Design Only)**

---

## 0. Positioning

This document describes **what comes *after* Phase 2**,  
without initiating or authorizing any implementation.

- Phase 2 itself remains **design-only**
- All phases described here are **inactive**
- No phase below is part of v0.7.x execution semantics

This file exists to prevent **accidental early execution** by clarifying sequence.

---

## 1. Phase 3 (Conceptual): Pragma Semantic Freezing

**Status:** Not started / Not authorized

### Purpose
- Fix the *meaning space* of `#pragma`
- Define semantic categories (e.g. intent, ethics, diagnostics)
- Still **no runtime effect**

### Explicit Limits
- No runtime binding
- No execution branching
- No evaluation logic
- No code

### Deliverables
- Markdown specification only
- Examples are illustrative, not executable

---

## 2. Phase 4 (Conceptual): Observational Runtime Attachment

**Status:** Not started / Not authorized

### Purpose
- Allow runtime to *observe* pragma presence
- Observation must be **side-effect free**
- Intended for diagnostics, logging, or metadata export

### Explicit Limits
- Execution result must remain identical
- Reduce semantics unchanged
- Reference runtime remains authoritative

### Deliverables
- Design document
- Non-normative diagrams (optional)

---

## 3. Phase 5 (Conceptual): Selective Semantic Influence

**Status:** Explicitly forbidden in v0.7.x

### Purpose (Future Only)
- Introduce *intent-aware behavior differences*
- Allow pragma to influence execution *by choice*

### Restrictions
- Requires new major/minor version
- Requires explicit opt-in
- Requires new reference semantics

> This phase is **out of scope** for current development.

---

## 4. Version Boundary Declaration

- v0.7.x: Execution determinism is absolute
- Semantic annotations are non-operative
- Any behavioral divergence belongs to **v0.8+ or later**

---

## 5. Safety Clause

If, while reading or extending this document:

- Implementation ideas arise
- Execution changes seem "easy"
- Reduce semantics feel "adjustable"

Then **stop immediately**.

This document is a map, not a trigger.

---

### Closing Note

Clarity of sequence is a safety mechanism.

Knowing *what comes later*  
is how we avoid doing it *now*.
