#pragma once

#include <flap/ast/ast.hpp>
#include <memory>
#include <string_view>

namespace flap {

std::unique_ptr<ast::Ast> parse(std::string_view doc);

}
