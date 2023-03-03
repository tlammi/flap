#pragma once

#include <flap/ast/expr.hpp>
#include <flap/ast/stmt.hpp>
#include <variant>
namespace flap::ast {

using Node = std::variant<Expr, Stmt>;

}  // namespace flap::ast
