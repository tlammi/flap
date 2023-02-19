#pragma once

#include <flap/ast/expr.hpp>
#include <flap/ast/func.hpp>
#include <flap/ast/stmt.hpp>
#include <variant>

namespace flap::ast {

template <class... Ts>
using Var = std::variant<const Ts*...>;

using Node = Var<Expr, Stmt>;

}  // namespace flap::ast
