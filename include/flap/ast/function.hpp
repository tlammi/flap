#pragma once

#include <flap/ast/ast.hpp>
#include <flap/ast/function_param.hpp>
#include <string_view>
#include <vector>

namespace flap::ast {

class Function : public Ast {
 public:
    virtual std::string_view return_type() const noexcept = 0;
    virtual std::string_view name() const noexcept = 0;

    virtual std::vector<const ast::FunctionParam*> params() const = 0;
    // TODO Ast -> Stmt
    virtual std::vector<const ast::Ast*> statements() const = 0;
};
}  // namespace flap::ast
