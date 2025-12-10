# Execution environment (symbol table, tensor registry, etc.)
# Minimal stub — will be extended in v0.8+

class Environment:
    def __init__(self):
        # Symbol table for tensors/functions/aggregators
        self.symbols = {}

    def set(self, name, value):
        self.symbols[name] = value

    def get(self, name):
        return self.symbols.get(name)
