#pragma once

#include <flap/ast/ast.hpp>
#include <memory>

namespace flap::lib::ast {

/**
 * Private side of an AST
 * */
class AstPriv {
 public:
    virtual ~AstPriv() {}

    virtual void add_function(std::unique_ptr<flap::ast::Function>&& f) = 0;
    //{
    //    throw std::runtime_error(
    //        "Function declaration in an unsupported scope");
    //}

 private:
};
}  // namespace flap::lib::ast
