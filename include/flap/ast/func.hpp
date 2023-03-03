#pragma once

#include <flap/ast/stmt.hpp>
#include <flap/types/string_view.hpp>
#include <vector>

namespace flap::ast {

struct Func {
    StringView name;
    StringView return_type;
    std::vector<Stmt> statements;
};
}  // namespace flap::ast
