#pragma once

#include <flap/ast/stmt.hpp>

namespace flap::ast {

class RetStmt : public Stmt {
 public:
    virtual const Expr& expr() const noexcept = 0;

 private:
};
}  // namespace flap::ast
