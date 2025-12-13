#include <iostream>

#include "tl/ir/builder.hpp"
#include "tl/parser/parser.hpp"
#include "tl/runtime/runtime.hpp"

int main() {
    // Minimal Tensor Logic snippet exercising grammar constructs.
    const std::string source = R"(
        A[i] = B[i] + C[i]
    )";


    try {
        tl::parser::Parser parser(source);
        auto ast = parser.parse_program();

        tl::ir::Builder builder;
        auto ir_program = builder.build(*ast);

        tl::runtime::RuntimePipeline runtime;
        runtime.initialize();
        runtime.run(ir_program);
        runtime.shutdown();
        std::cout << "Demo pipeline completed (no-op execution)." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
