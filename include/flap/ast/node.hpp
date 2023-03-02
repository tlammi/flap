#pragma once

#include <flap/ast/expr.hpp>
#include <variant>
namespace flap::ast {

using Node = std::variant<Expr>;

}  // namespace flap::ast
