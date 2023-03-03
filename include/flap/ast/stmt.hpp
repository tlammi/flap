#pragma once

#include <flap/ast/ret_stmt.hpp>
#include <flap/ast/var_def.hpp>
#include <variant>

namespace flap::ast {

struct Func;
using Stmt = std::variant<VarDef, Func, RetStmt>;
}  // namespace flap::ast
