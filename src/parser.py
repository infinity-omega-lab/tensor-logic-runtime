from dataclasses import dataclass
from typing import List, Optional, Any, Dict
from .ast import (
    Program, Assign, Accumulate, TensorRef, FuncCall,
    AggregatorCall, Sum, Product, Number, Pragma
)
from .ast import Position


# --------------------------------------------------------------
# Token model (for illustration)
# --------------------------------------------------------------
@dataclass
class Token:
    type: str
    value: str
    line: int
    col: int


# --------------------------------------------------------------
# Parser core class
# --------------------------------------------------------------
class Parser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.pos = 0

    # ------------------------------
    # Helpers
    # ------------------------------
    def peek(self) -> Optional[Token]:
        return self.tokens[self.pos] if self.pos < len(self.tokens) else None

    def prev(self) -> Optional[Token]:
        return self.tokens[self.pos - 1] if self.pos > 0 else None

    def accept(self, typ: str, value: str = None) -> bool:
        t = self.peek()
        if t and t.type == typ and (value is None or t.value == value):
            self.pos += 1
            return True
        return False

    def expect(self, typ: str, value: str = None) -> Token:
        t = self.peek()
        if not t or t.type != typ or (value is not None and t.value != value):
            raise SyntaxError(f"Expected {typ}{'='+value if value else ''} at {t.line}:{t.col}")
        self.pos += 1
        return t

    def parse_identifier(self) -> str:
        t = self.expect("ID")
        return t.value

    # ------------------------------
    # Entry point
    # ------------------------------
    def parse_program(self) -> Program:
        stmts = []
        while True:
            tok = self.peek()
            if not tok or tok.type == "EOF":
                break
            if tok.type == "HASH":
                stmts.append(self.parse_pragma())
            else:
                stmts.append(self.parse_statement())
        return Program(stmts)

    # ------------------------------
    # Statement dispatch
    # ------------------------------
    def parse_statement(self):
        term = self.parse_term()

        if isinstance(term, (AggregatorCall, FuncCall)):
            return term

        if not isinstance(term, TensorRef):
            raise SyntaxError("Statement must begin with tensor reference, function, or aggregator call")

        if self.accept("ACCUM"):  # +=, max=, avg=
            op = self.prev().value
            rhs = self.parse_expr()
            return Accumulate(term, op, rhs)
        self.expect("OP", "=")
        rhs = self.parse_expr()
        return Assign(term, rhs)

    # ------------------------------
    # Expressions
    # ------------------------------
    def parse_expr(self):
        term = self.parse_product()
        while self.accept("OP", "+"):
            rhs = self.parse_product()
            term = Sum(term, rhs)
        return term

    def parse_product(self):
        factors = [self.parse_term()]
        while True:
            tok = self.peek()
            if not tok or tok.type in {"OP", "COMMA", "RPAREN", "RBRACE", "ACCUM", "EOF"}:
                break
            if tok.type in {"ID", "NUMBER", "LPAREN"}:
                factors.append(self.parse_term())
            else:
                break
        if len(factors) == 1:
            return factors[0]
        return Product(factors)

    # ------------------------------
    # Term (tensor, function, aggregator, number)
    # ------------------------------
    def parse_term(self):
        tok = self.peek()
        if not tok:
            raise SyntaxError("Unexpected EOF")

        # Number literal
        if tok.type == "NUMBER":
            self.pos += 1
            return Number(float(tok.value))

        # Identifier-based term
        if tok.type == "ID":
            name = self.parse_identifier()

            # Aggregator: sum[i](expr)
            if self.accept("LBRACKET"):  # "["
                indices = self.parse_index_list()
                self.expect("RBRACKET")  # "]"
                if self.accept("LPAREN"):  # "("
                    args = self.parse_arg_list()
                    self.expect("RPAREN")  # ")"
                    return AggregatorCall(name, indices, args)
                return TensorRef(name, indices)

            # Function call: f(x)
            elif self.accept("LPAREN"):
                args = self.parse_arg_list()
                self.expect("RPAREN")
                return FuncCall(name, args)

            # Plain tensor reference
            return TensorRef(name, [])

        # Parenthesized expression
        if self.accept("LPAREN"):
            expr = self.parse_expr()
            self.expect("RPAREN")
            return expr

        raise SyntaxError(f"Unexpected token {tok.type} '{tok.value}' at {tok.line}:{tok.col}")

    # ------------------------------
    # Index / argument lists
    # ------------------------------
    def parse_index_list(self):
        indices = [self.parse_identifier()]
        while self.accept("COMMA"):
            indices.append(self.parse_identifier())
        return indices

    def parse_arg_list(self):
        args = [self.parse_expr()]
        while self.accept("COMMA"):
            args.append(self.parse_expr())
        return args

    def parse_tensor_ref(self):
        name = self.parse_identifier()
        if self.accept("LBRACKET"):
            indices = self.parse_index_list()
            self.expect("RBRACKET")
            return TensorRef(name, indices)
        return TensorRef(name, [])

    # ------------------------------
    # Pragma (#pragma ethical {...})
    # ------------------------------
    def parse_pragma(self):
        self.expect("HASH")
        self.expect("PRAGMA")
        kind = self.parse_identifier()
        self.expect("LBRACE")
        spec = self.parse_pragma_fields()
        self.expect("RBRACE")
        return Pragma(kind, spec)

    def parse_pragma_fields(self) -> Dict[str, str]:
        fields = {}
        while True:
            key = self.parse_identifier()
            self.expect("COLON")
            val_tok = self.expect("STRING")
            fields[key] = val_tok.value.strip('"')
            if not self.accept("COMMA"):
                break
        return fields
