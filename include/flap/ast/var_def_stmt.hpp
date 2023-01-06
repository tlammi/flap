#pragma once

#include <flap/ast/stmt.hpp>

namespace flap::ast {

/**
 * Variable definition statement
 * */
class VarDefStmt : public Stmt {
 public:
    virtual const Expr& expr() const noexcept = 0;
    virtual std::string_view name() const noexcept = 0;
    virtual std::string_view type() const noexcept = 0;

 private:
};

}  // namespace flap::ast
