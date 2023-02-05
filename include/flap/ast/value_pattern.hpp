#pragma once

#include <flap/ast/expr.hpp>
#include <flap/ast/pattern.hpp>
#include <flap/ast/stmt.hpp>

namespace flap::ast {

class ValuePattern : public Pattern {
 public:
    virtual const Expr& expr() const noexcept = 0;
    virtual std::vector<const Stmt*> statements() const noexcept = 0;
};
}  // namespace flap::ast
