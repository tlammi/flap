#pragma once

#include <flap/ast/ast.hpp>
#include <string_view>
namespace flap::ast {

class FunctionParam : public Ast {
 public:
    virtual std::string_view name() const noexcept = 0;
    virtual std::string_view type() const noexcept = 0;

 private:
};

}  // namespace flap::ast
