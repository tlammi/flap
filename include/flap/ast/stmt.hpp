#pragma once

#include <flap/ast/var_def.hpp>
#include <variant>

namespace flap::ast {

using Stmt = std::variant<VarDef>;
}
