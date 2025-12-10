# AST evaluator stub — v0.7 public release keeps this intentionally minimal.
# Real execution semantics will be implemented in v0.8+.

from ..ast import (
    Assign, Accumulate, FuncCall, AggregatorCall,
    TensorRef, Number, Sum, Product, Pragma
)
from .runtime_error import RuntimeErrorTL

class Evaluator:
    def __init__(self, env):
        self.env = env

    def eval(self, node):
        """Dispatch evaluator (stub)."""
        t = type(node)

        if t is Assign:
            # Placeholder: semantic path only
            return ("assign", node.target.name)

        if t is Accumulate:
            return ("accumulate", node.target.name, node.op)

        if t is FuncCall:
            return ("func", node.name)

        if t is AggregatorCall:
            return ("agg", node.name)

        if t is TensorRef:
            return ("tensor", node.name)

        if t is Number:
            return node.value

        if t is Sum:
            return ("sum", self.eval(node.left), self.eval(node.right))

        if t is Product:
            return ("prod", [self.eval(t) for t in node.terms])

        if t is Pragma:
            return ("pragma", node.kind)

        raise RuntimeErrorTL(f"Unknown AST node: {t}")
