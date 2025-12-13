#pragma once

#include <memory>
#include <string>

#include "tl/ir/ir.hpp"

namespace tl::runtime {

// Layer stubs per diagrams; inner algorithms are intentionally TODO.
class PCL {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

class SMM {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

class TIL {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

class GDA {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

class AOL {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

class DRA {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

class UCG {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

class RDE {
public:
    void initialize();
    void process(ir::Program& program);
    void shutdown();
};

// RuntimePipeline wires layer order based on tl_runtime_v0_7_overview.md and TOC.
class RuntimePipeline {
public:
    RuntimePipeline();
    ~RuntimePipeline();

    void initialize();
    void run(ir::Program& program);
    void shutdown();

private:
    PCL pcl_;
    SMM smm_;
    TIL til_;
    GDA gda_;
    AOL aol_;
    DRA dra_;
    UCG ucg_;
    RDE rde_;
    bool initialized_{false};
};

}  // namespace tl::runtime
