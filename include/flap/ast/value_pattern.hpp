#pragma once

#include <flap/ast/pattern.hpp>
#include <lap/ast/expr.hpp>

namespace flap::ast {

class ValuePattern : public Pattern {
 public:
    virtual const Expr& expr() const noexcept = 0;
};
}  // namespace flap::ast
