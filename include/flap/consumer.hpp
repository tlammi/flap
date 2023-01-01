#pragma once

#include <flap/ast/ast.hpp>
#include <flap/ast/function.hpp>
#include <flap/ast/int_literal.hpp>
#include <flap/ast/module.hpp>
#include <flap/ast/ret_stmt.hpp>
#include <memory>

namespace flap {

/// Control if the AST should recurse into its children when consuming
enum class Recurse { No, Yes };

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

    virtual Recurse consume(const ast::Module& module_) { return Recurse::Yes; }
    virtual Recurse consume(const ast::Function& func) { return Recurse::Yes; }
    virtual Recurse consume(const ast::RetStmt& ret) { return Recurse::Yes; }
    virtual Recurse consume(const ast::IntLiteral& lit) { return Recurse::Yes; }
};

/**
 * Consumer generating LLVM IR
 * */
std::unique_ptr<Consumer> llvm_consumer();

/// Produces information about the parsed code
std::unique_ptr<Consumer> debug_consumer();

}  // namespace flap
