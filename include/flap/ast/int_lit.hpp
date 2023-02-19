#pragma once

namespace flap::ast {

/**
 * Integer literals
 * */
struct IntLit {
    int radix;
    std::string_view value;
};
}  // namespace flap::ast
