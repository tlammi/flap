#pragma once

#include <flap/ast/expr.hpp>

namespace flap::ast {

class FunctionCall : public Expr {
 public:
    virtual std::string_view name() const noexcept = 0;
    virtual std::vector<const ast::Expr*> args() const = 0;

 private:
};
}  // namespace flap::ast
