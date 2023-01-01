#pragma once

#include <filesystem>
#include <flap/ast/ast.hpp>
#include <flap/doc.hpp>
#include <istream>
#include <memory>
#include <string_view>

namespace flap {

std::unique_ptr<ast::Ast> parse_view(std::string_view doc);
Doc parse(std::istream& s);
Doc parse_file(const std::filesystem::path& path);

}  // namespace flap
