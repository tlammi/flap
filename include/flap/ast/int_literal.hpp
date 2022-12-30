#pragma once

#include <flap/ast/ast.hpp>
#include <string_view>

namespace flap::ast {

class IntLiteral : public Ast {
    static constexpr std::string_view hex = "0x";
    static constexpr std::string_view bin = "0b";

 public:
    explicit IntLiteral(std::string_view value) : m_value{value} {}
    void accept(Consumer& consumer) const override;

    /// Whole literal value
    std::string_view value() const noexcept { return m_value; }

    /// Radix of the literal
    uint8_t radix() const noexcept {
        if (value().starts_with(hex)) return 16;
        if (value().starts_with(bin)) return 2;
        return 10;
    }

    /// Value without prefix such as 0x
    std::string_view raw_value() const noexcept {
        if (value().starts_with(hex)) return value().substr(hex.size());
        if (value().starts_with(bin)) return value().substr(bin.size());
        return value();
    }

 private:
    std::string_view m_value;
};
}  // namespace flap::ast
