# src/visitors.py
from dataclasses import is_dataclass, fields
from typing import Any


def ast_to_json(node: Any):
    if isinstance(node, list):
        return [ast_to_json(n) for n in node]
    if isinstance(node, dict):
        return {k: ast_to_json(v) for k, v in node.items()}
    if isinstance(node, (int, float, str)) or node is None:
        return node
    if not is_dataclass(node):
        return repr(node)

    payload = {}
    for f in fields(node):
        if f.name == "pos":
            continue
        value = getattr(node, f.name)
        if value is None:
            continue
        payload[f.name] = ast_to_json(value)
    return {node.__class__.__name__: payload}
