# tests/test_lexer_parser.py
import json
from pathlib import Path
from src.lexer import tokenize
from src.parser import Parser
from src.visitors import ast_to_json

CASES = [
    ("simple_assignment.tl", "simple_assignment.json"),
    ("aggregator_call.tl",   "aggregator_call.json"),
    ("pragma_ethical.tl",    "pragma_ethical.json"),
]

def load_text(p): return Path(p).read_text(encoding="utf-8")
def load_json(p): return json.loads(Path(p).read_text(encoding="utf-8"))

BASE = Path(__file__).parent
FX = BASE / "fixtures"
GD = BASE / "golden"

def parse_file(fname: str):
    toks = tokenize(load_text(FX / fname))
    ast = Parser(toks).parse_program()
    return ast_to_json(ast.statements)

def test_all_cases():
    for tl, gj in CASES:
        got = parse_file(tl)
        want = load_json(GD / gj)
        assert got == want, f"AST mismatch for {tl}"
