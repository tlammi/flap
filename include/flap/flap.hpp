#pragma once

#include <flap/ast/node.hpp>
#include <string>
namespace flap {

struct Parsed {
    std::string doc;
    ast::Node root;
};

Parsed parse(std::string doc);

}  // namespace flap
