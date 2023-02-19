#pragma once

#include <flap/ast/expr.hpp>
#include <string_view>

namespace flap::ast {
struct UnOp {
    std::string_view op;
    Expr operand;
};
}  // namespace flap::ast
