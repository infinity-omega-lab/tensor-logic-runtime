#include <cassert>
#include <iostream>

#include "tl/ir/builder.hpp"
#include "tl/parser/parser.hpp"
#include "tl/runtime/runtime.hpp"

int main() {
    const std::string source = R"(
# simple assign
X[i] = Y[i] + 1
# pragma for diagnostics
#pragma diag { level:"trace" }
Z[*k] max= agg[k] ( foo(X[i], Y[i]) )
)";

    tl::parser::Parser parser(source);
    auto ast = parser.parse_program();
    assert(ast);
    assert(!ast->statements.empty());

    tl::ir::Builder builder;
    auto ir_program = builder.build(*ast);
    assert(!ir_program.instructions.empty());

    tl::runtime::RuntimePipeline runtime;
    runtime.initialize();
    runtime.run(ir_program);
    runtime.shutdown();

    std::cout << "parser_runtime_smoke passed\n";
    return 0;
}
