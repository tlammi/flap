#pragma once

#include <flap/ast/var_def.hpp>
#include <variant>

namespace flap::ast {

struct Func;
using Stmt = std::variant<VarDef, Func>;
}  // namespace flap::ast
