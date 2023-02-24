#pragma once

#include <flap/types/string_view.hpp>

namespace flap::ast {

struct IntLit {
    constexpr int radix() const noexcept {
        if (value.starts_with("0x")) return 16;
        if (value.starts_with("0b")) return 2;
        return 10;
    }

    StringView value;
};

}  // namespace flap::ast
