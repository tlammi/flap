#pragma once

#include <flap/ast/expr.hpp>
#include <string_view>

namespace flap::ast {

/**
 * Binary operator
 *
 * (expr) (operator) (expr)
 * */
struct BinOp {
    std::string_view op;
    Expr lhs;
    Expr rhs;
};

}  // namespace flap::ast
