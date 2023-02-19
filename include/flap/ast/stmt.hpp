#pragma once

#include <variant>
namespace flap::ast {

class RetStmt;

template <class... Ts>
using Var = std::variant<const Ts*...>;

using Stmt = Var<RetStmt>;
}  // namespace flap::ast
