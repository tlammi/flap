#pragma once

#include <flap/ast/ast.hpp>
#include <string_view>
#include <vector>

namespace flap::ast {

class Function : public Ast {
 public:
    virtual std::string_view return_type() const noexcept = 0;
    virtual std::string_view name() const noexcept = 0;

    virtual std::vector<const ast::Ast*> statements() const = 0;
};
}  // namespace flap::ast
