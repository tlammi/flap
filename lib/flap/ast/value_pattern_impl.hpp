#pragma once

#include <flap/ast/value_pattern.hpp>
#include <memory>

namespace flap::ast {

class ValuePatternImpl final : public ValuePattern {
 public:
    ValuePatternImpl(std::unique_ptr<Expr> expr) : m_expr{std::move(expr)} {}

    const Expr& expr() const noexcept override { return *m_expr; }

    void accept(Consumer& consumer) const { consumer.consume(*this); }

 private:
    std::unique_ptr<Expr> m_expr;
};
}  // namespace flap::ast
