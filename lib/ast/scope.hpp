#pragma once

#include <flap/ast/function.hpp>
#include <flap/ast/int_literal.hpp>

namespace flap::ast {

/**
 * Scope is an entity which can contain other ASTs
 *
 * This is generally inherited by AST implementations and used in parsing to
 * construct ASTs.
 *
 * */
template <class T>
class Scope {
 public:
    virtual ~Scope() {}

    virtual void add(std::unique_ptr<T>&& entry) = 0;
};

using FunctionScope = Scope<Function>;
using IntLiteralScope = Scope<IntLiteral>;

}  // namespace flap::ast
