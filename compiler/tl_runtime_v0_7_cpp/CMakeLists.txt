cmake_minimum_required(VERSION 3.16)

project(tl_runtime_v0_7_cpp LANGUAGES CXX)

option(TL_RUNTIME_BUILD_TESTS "Build tests for TL Runtime v0.7" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(tl_runtime_v0_7
    src/parser/lexer.cpp
    src/parser/parser.cpp
    src/ir/ir.cpp
    src/ir/builder.cpp
    src/runtime/runtime.cpp
)

target_include_directories(tl_runtime_v0_7
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(tl_runtime_v0_7_demo src/main.cpp)
target_link_libraries(tl_runtime_v0_7_demo PRIVATE tl_runtime_v0_7)

if(TL_RUNTIME_BUILD_TESTS)
    enable_testing()
    add_executable(tl_runtime_v0_7_tests tests/parser_runtime_smoke.cpp)
    target_link_libraries(tl_runtime_v0_7_tests PRIVATE tl_runtime_v0_7)
    add_test(NAME tl_runtime_v0_7_smoke COMMAND tl_runtime_v0_7_tests)
endif()
