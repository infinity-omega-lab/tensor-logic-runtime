# Example: Minimal Reduce-Based Execution in Tensor Logic Runtime

## Purpose of This Example

This example demonstrates the **minimal complete execution path** of the
Tensor Logic Runtime based on **reduce semantics**.

Its sole purpose is to show:

- how a Tensor Logic expression is executed end-to-end,
- where semantic meaning is determined,
- and how deterministic behavior is guaranteed.

This is **not** an example of expressive power.
It is an example of **semantic correctness**.

---

## What This Example Shows

This example illustrates the following execution stages:

1. A Tensor Logic expression is parsed into an AST.
2. The AST is lowered into an intermediate representation (IR).
3. Domains for all variables are explicitly bound.
4. A deterministic reduce execution plan is generated.
5. The plan is executed by the ReduceExecutor.
6. A single, reproducible result is produced.

All execution passes through the canonical path:

DomainBinder → ReducePlan → ReduceExecutor

There are no shortcuts, optimizations, or implicit inferences.

---

## What This Example Does *Not* Show

To avoid ambiguity, this example intentionally excludes:

- average (avg=) or maximum (max=) aggregation,
- non-linear functions (e.g. step, sigmoid, softmax),
- implicit domain inference,
- parallel execution,
- execution reordering or optimization,
- learning, training, or probabilistic behavior.

These features are **out of scope for v1.0** and are deliberately omitted.

---

## Why Reduce Semantics Only

In Tensor Logic Runtime v1.0, **reduce semantics are the only point where
semantic meaning is committed**.

Before reduction:

- expressions describe structure,
- variables are symbolic,
- no interpretation is finalized.

During reduction:

- all variable domains are fixed,
- all operations are executed deterministically,
- the result becomes unambiguous and final.

This example is designed to make that boundary explicit.

---

## Expected Outcome

Running this example should demonstrate that:

- the same input always produces the same output,
- the execution order is fixed and inspectable,
- semantic meaning is determined only once,
- and the runtime does not perform any hidden inference.

If the reader understands **where and why the result becomes final**,
the example has succeeded.

---

## Scope and Version Context

This example is valid for:

- Tensor Logic Runtime v0.7.2 (reference semantics)
- Tensor Logic Runtime v1.0-draft

It serves as the canonical demonstration of
**deterministic reduce execution** in the Tensor Logic Runtime.
