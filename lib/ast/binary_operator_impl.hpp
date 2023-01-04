#pragma once

#include <flap/ast/binary_operator.hpp>
#include <flap/consumer.hpp>

#include "ast/scope.hpp"

namespace flap::ast {

class BinaryOperatorImpl final : public BinaryOperator {
 public:
    BinaryOperatorImpl(std::string_view oper, std::unique_ptr<Expr> lhs,
                       std::unique_ptr<Expr> rhs)
        : m_oper{oper}, m_lhs{std::move(lhs)}, m_rhs{std::move(rhs)} {}

    void accept(Consumer& consumer) const override {
        auto recurse = consumer.consume(*this);
        if (recurse == Recurse::Yes) {
            m_lhs->accept(consumer);
            m_rhs->accept(consumer);
        }
    }
    std::string_view oper() const override { return m_oper; }
    const Expr& lhs() const override { return *m_lhs; }
    const Expr& rhs() const override { return *m_rhs; }

 private:
    std::string_view m_oper;
    std::unique_ptr<Expr> m_lhs;
    std::unique_ptr<Expr> m_rhs;
};
}  // namespace flap::ast
