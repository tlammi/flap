#pragma once

#include <flap/ast/ast.hpp>
#include <flap/ast/function.hpp>
#include <flap/ast/int_literal.hpp>
#include <flap/ast/module.hpp>
#include <memory>

namespace flap {

/**
 * Base class for consuming ASTs
 *
 * Implementations of Consumers can consume ASTs.
 *
 * For example of Consumer are code generator
 * */
class Consumer {
 public:
    Consumer() = default;
    virtual ~Consumer() = default;

    virtual void consume(const ast::Module& module_) = 0;
    virtual void consume(const ast::Function& func) = 0;
    virtual void consume(const ast::IntLiteral& lit) = 0;
};

/**
 * Consumer generating LLVM IR
 * */
std::unique_ptr<Consumer> llvm_consumer();

/// Produces information about the parsed code
std::unique_ptr<Consumer> debug_consumer();

}  // namespace flap
