#pragma once

#include <flap/ast/value_pattern.hpp>
#include <memory>

namespace flap::ast {

class ValuePatternImpl final : public ValuePattern {
 public:
    ValuePatternImpl(std::unique_ptr<Expr> expr) : m_expr{std::move(expr)} {}

    const Expr& expr() const noexcept override { return *m_expr; }

    void accept(Consumer& consumer) const { consumer.consume(*this); }

    std::vector<const Stmt*> statements() const noexcept {
        std::vector<const Stmt*> out{};
        for (const auto& stmt : m_stmts) {
            out.push_back(stmt.get());
        }
        return out;
    }

    void add_statement(std::unique_ptr<Stmt> stmt) {
        m_stmts.push_back(std::move(stmt));
    }

 private:
    std::unique_ptr<Expr> m_expr;
    std::vector<std::unique_ptr<Stmt>> m_stmts{};
};
}  // namespace flap::ast
