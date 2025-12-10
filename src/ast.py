# src/ast.py
from dataclasses import dataclass
from typing import List, Dict, Any, Optional


# ---------------------------------------
# Position info (optional)
# ---------------------------------------
@dataclass
class Position:
    line: int = 0
    col: int = 0


# ---------------------------------------
# Program (top-level)
# ---------------------------------------
@dataclass
class Program:
    statements: List[Any]
    pos: Optional[Position] = None


# ---------------------------------------
# Basic expression nodes
# ---------------------------------------
@dataclass
class TensorRef:
    name: str
    indices: List[str]
    pos: Optional[Position] = None


@dataclass
class Number:
    value: float
    pos: Optional[Position] = None


# ---------------------------------------
# Expression operators
# ---------------------------------------
@dataclass
class Sum:
    left: Any
    right: Any
    op: str = "+"
    pos: Optional[Position] = None


@dataclass
class Product:
    terms: List[Any]
    pos: Optional[Position] = None


# ---------------------------------------
# Function & aggregator
# ---------------------------------------
@dataclass
class FuncCall:
    name: str
    args: List[Any]
    pos: Optional[Position] = None


@dataclass
class AggregatorCall:
    name: str
    indices: List[str]
    args: List[Any]
    pos: Optional[Position] = None


# ---------------------------------------
# Statements
# ---------------------------------------
@dataclass
class Assign:
    target: TensorRef
    value: Any
    pos: Optional[Position] = None


@dataclass
class Accumulate:
    target: TensorRef
    op: str       # '+=', 'max=', etc.
    value: Any
    pos: Optional[Position] = None


# ---------------------------------------
# Pragma
# ---------------------------------------
@dataclass
class Pragma:
    kind: str
    spec: Dict[str, Any]
    pos: Optional[Position] = None
