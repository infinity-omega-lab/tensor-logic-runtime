# Reference TensorStore Design (TL Runtime v0.7.1)

## Purpose
TensorStore is a semantics-free value container used by the reference interpreter.
It exists solely to store and retrieve tensor values deterministically.

## Design Principles
- Correctness over performance
- Deterministic behavior
- No semantic logic (reduce, projection, pragma unaware)
- Simple, replaceable implementation

## Responsibilities
- Register tensors with fixed shapes
- Provide get/set access by coordinates
- Return default value (0.0) for uninitialized elements

## Non-Goals
- No projection logic (sum/max/avg)
- No index interpretation
- No memory optimization
- No parallelism

## API Summary
- register_tensor(TensorId, shape)
- get(TensorId, Coord) -> Value
- set(TensorId, Coord, Value)

## Rationale
This design intentionally favors clarity and replaceability.
Optimized runtimes are expected to replace this component entirely,
while preserving its observable behavior.
