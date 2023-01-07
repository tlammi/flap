#pragma once

#include <flap/ast/identifier_expr.hpp>

namespace flap::ast {
class IdentifierExprImpl final : public IdentifierExpr {
 public:
    IdentifierExprImpl(std::string_view name) : m_name{name} {}
    std::string_view name() const noexcept override { return m_name; }

    void accept(Consumer& consumer) const override { consumer.consume(*this); }

 private:
    std::string_view m_name{};
};
}  // namespace flap::ast
