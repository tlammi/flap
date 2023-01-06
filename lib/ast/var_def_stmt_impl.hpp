#pragma once

#include <flap/ast/var_def_stmt.hpp>

namespace flap::ast {

class VarDefStmtImpl final : public VarDefStmt {
 public:
    VarDefStmtImpl(std::string_view name, std::string_view type,
                   std::unique_ptr<Expr> expr)
        : m_name{name}, m_type{type}, m_expr{std::move(expr)} {}

    void accept(Consumer& consumer) const override { consumer.consume(*this); }

    std::string_view name() const noexcept override { return m_name; }
    std::string_view type() const noexcept override { return m_type; }
    const Expr& expr() const noexcept override { return *m_expr; }

 private:
    std::string_view m_name;
    std::string_view m_type;
    std::unique_ptr<Expr> m_expr{};
};
}  // namespace flap::ast
