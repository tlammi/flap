#pragma once

#include <flap/ast/expr.hpp>
namespace flap::ast {

/**
 * (Function) return statement
 * */
struct RetStmt {
    Expr expr;
};

}  // namespace flap::ast
