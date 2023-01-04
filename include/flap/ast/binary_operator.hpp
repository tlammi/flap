#pragma once

#include <flap/ast/expr.hpp>
#include <string_view>

namespace flap::ast {

class BinaryOperator : public Expr {
 public:
    virtual std::string_view oper() const = 0;

    virtual const Expr& lhs() const = 0;
    virtual const Expr& rhs() const = 0;

 private:
};
}  // namespace flap::ast
