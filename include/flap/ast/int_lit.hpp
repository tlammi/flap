#pragma once

#include <flap/types/string_view.hpp>

namespace flap::ast {

class IntLit {
    static constexpr std::string_view hex = "0x";
    static constexpr std::string_view bin = "0b";

 public:
    constexpr explicit IntLit(StringView val) : m_val{val} {}
    constexpr int radix() const noexcept {
        if (m_val.starts_with(hex)) return 16;
        if (m_val.starts_with(bin)) return 2;
        return 10;
    }

    constexpr StringView value() const noexcept {
        if (m_val.starts_with(hex) || m_val.starts_with(bin))
            return m_val.substr(2);
        return m_val;
    }

    constexpr StringView raw_value() const noexcept { return m_val; }

 private:
    StringView m_val;
};

}  // namespace flap::ast
