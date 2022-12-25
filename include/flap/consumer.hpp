#pragma once

#include <flap/ast/ast.hpp>
#include <flap/ast/function.hpp>
#include <flap/ast/int_literal.hpp>
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
    virtual ~Consumer() {}

    virtual void consume(const ast::Function& func);
    virtual void consume(const ast::IntLiteral& lit);
};

std::unique_ptr<Consumer> llvm_consumer();

}  // namespace flap
