#pragma once

#include <filesystem>
#include <flap/ast/node.hpp>
#include <istream>
#include <memory>
#include <string_view>

namespace flap {

class Root {
 public:
    virtual ~Root() {}

    virtual ast::Node node() const = 0;
};

std::unique_ptr<Root> parse(std::string str);

}  // namespace flap
