#pragma once

#include <string_view>

namespace flap::ast {

/**
 * Expression for identifier evaluation
 * */
struct IdenExpr {
    std::string_view name;
};

}  // namespace flap::ast
