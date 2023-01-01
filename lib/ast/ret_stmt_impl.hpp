#pragma once

#include <flap/ast/ret_stmt.hpp>

namespace flap::ast {

class RetStmtImpl final : public RetStmt, public ExprScope {
 public:
    void accept(Consumer& consumer) const override {
        auto recurse = consumer.consume(*this);
        if (recurse == Recurse::Yes) m_expr->accept(consumer);
    }

    void add(std::unique_ptr<Expr>&& expr) override {
        m_expr = std::move(expr);
    }

    const Expr& expr() const noexcept override { return *m_expr; }

 private:
    std::unique_ptr<Expr> m_expr{};
};
}  // namespace flap::ast
