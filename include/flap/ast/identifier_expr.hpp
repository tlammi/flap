#pragma once

#include <flap/ast/expr.hpp>
namespace flap::ast {

class IdentifierExpr : public Expr {
 public:
    virtual std::string_view name() const noexcept = 0;

 private:
};

}  // namespace flap::ast
