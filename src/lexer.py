# src/lexer.py
from dataclasses import dataclass

@dataclass
class Token:
    type: str
    value: str
    line: int
    col: int


def tokenize(text: str):
    tokens = []
    i = 0
    line = 1
    col = 1

    def emit(t, v):
        tokens.append(Token(t, v, line, col))

    n = len(text)

    while i < n:
        c = text[i]

        # ---------------------------------------
        # Newline
        # ---------------------------------------
        if c == "\n":
            i += 1
            line += 1
            col = 1
            continue

        # ---------------------------------------
        # Whitespace
        # ---------------------------------------
        if c.isspace():
            i += 1
            col += 1
            continue

        # ---------------------------------------
        # Comments or pragma
        # ---------------------------------------
        if c == "#":
            # Look ahead to see if this is "#pragma"
            j = i + 1
            # skip whitespace
            while j < n and text[j].isspace():
                j += 1

            # If "#pragma"
            if text.startswith("pragma", j):
                emit("HASH", "#")
                i += 1
                col += 1
                continue

            # Otherwise treat as a FULL-LINE COMMENT → ignore to newline
            while i < n and text[i] != "\n":
                i += 1
            continue

        # ---------------------------------------
        # Identifier
        # ---------------------------------------
        if c.isalpha() or c == "_":
            start = i
            while i < n and (text[i].isalnum() or text[i] == "_"):
                i += 1
            value = text[start:i]
            col += (i - start)
            if value == "pragma":
                emit("PRAGMA", value)
            else:
                emit("ID", value)
            continue

        # ---------------------------------------
        # Numbers
        # ---------------------------------------
        if c.isdigit():
            start = i
            while i < n and (text[i].isdigit() or text[i] == "."):
                i += 1
            emit("NUMBER", text[start:i])
            col += (i - start)
            continue

        # ---------------------------------------
        # Operators
        # ---------------------------------------
        if c in "+=":
            if c == "+" and i + 1 < n and text[i+1] == "=":
                emit("ACCUM", "+=")
                i += 2
                col += 2
                continue
            emit("OP", c)
            i += 1
            col += 1
            continue

        # ---------------------------------------
        # Symbols
        # ---------------------------------------
        if c == "(":
            emit("LPAREN", "(")
            i += 1; col += 1; continue
        if c == ")":
            emit("RPAREN", ")")
            i += 1; col += 1; continue
        if c == "[":
            emit("LBRACKET", "[")
            i += 1; col += 1; continue
        if c == "]":
            emit("RBRACKET", "]")
            i += 1; col += 1; continue
        if c == ",":
            emit("COMMA", ",")
            i += 1; col += 1; continue
        if c == "{":
            emit("LBRACE", "{")
            i += 1; col += 1; continue
        if c == "}":
            emit("RBRACE", "}")
            i += 1; col += 1; continue
        if c == ":":
            emit("COLON", ":")
            i += 1; col += 1; continue
        if c == "\"":
            # string literal
            start = i + 1
            i += 1
            while i < n and text[i] != "\"":
                i += 1
            value = text[start:i]
            emit("STRING", f"\"{value}\"")
            i += 1  # skip closing quote
            col += (i - start + 1)
            continue

        # ---------------------------------------
        # Unexpected character
        # ---------------------------------------
        raise SyntaxError(f"Unexpected character '{c}' at line {line}")

    tokens.append(Token("EOF", "", line, col))
    return tokens
