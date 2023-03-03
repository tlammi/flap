#pragma once

#include <flap/ast/expr.hpp>
#include <flap/types/string_view.hpp>

namespace flap::ast {

struct VarDef {
    StringView name;
    StringView type;
    Expr expr;
};

}  // namespace flap::ast
