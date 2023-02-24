#pragma once

#include <flap/ast/int_lit.hpp>
#include <variant>

namespace flap::ast {

using Expr = std::variant<IntLit>;

}
