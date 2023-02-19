#pragma once

#include <flap/ast/func_param.hpp>
#include <flap/ast/stmt.hpp>
#include <flap/ast/type.hpp>
#include <vector>

namespace flap::ast {

struct Func {
    std::string_view name;
    std::vector<Stmt> statements;
    std::vector<const FuncParam*> param{};
    const Type* type;
};
}  // namespace flap::ast
