#pragma once

#include <flap/ast/function.hpp>
#include <flap/ast/int_literal.hpp>

namespace flap::ast {

/**
 * Scope is an entity which can contain other ASTs
 *
 * Pretty much every AST class inherits this and handles all sub-ASTs it
 * supports and throws otherwise.
 * */
class Scope {
 public:
    virtual ~Scope() {}

    /**
     * Add a new function to the scope
     * */
    virtual void add_function(std::unique_ptr<Function>&& f) { do_throw(); }
    virtual void add_int_literal(std::unique_ptr<IntLiteral>&& i) {
        do_throw();
    }

 private:
    [[noreturn]] static void do_throw() {
        throw std::runtime_error("Unsupported AST in this scope");
    }
};

}  // namespace flap::ast
