#pragma once

#include <flap/ast/expr.hpp>
#include <flap/ast/type.hpp>

namespace flap::ast {

struct FuncParam {
    std::string_view name;
    const Type* type;
};

}  // namespace flap::ast
