#pragma once

#include <flap/ast/ast.hpp>
#include <string>
namespace flap {

struct Doc {
    std::string data;
    std::unique_ptr<ast::Ast> root;
};
}  // namespace flap
