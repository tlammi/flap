#pragma once

#include <flap/types/string_view.hpp>

namespace flap::ast {

/**
 * Identifier expression
 *
 * E.g
 * ```
 * foo: i32 := 100
 * foo // <== This
 * ```
 * */
struct IdenExpr {
    StringView name;
};
}  // namespace flap::ast

