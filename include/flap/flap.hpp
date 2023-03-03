#pragma once

#include <flap/ast/access.hpp>
#include <flap/ast/func.hpp>
#include <flap/ast/node.hpp>
#include <string>
namespace flap {

struct Parsed {
    explicit Parsed(std::string doc);
    ~Parsed() = default;

    Parsed(const Parsed&) = delete;
    Parsed& operator=(const Parsed&) = delete;

    Parsed(Parsed&&) noexcept = default;
    Parsed& operator=(Parsed&&) noexcept = default;

    std::string doc;
    ast::Node root;
};

Parsed parse(std::string doc);

}  // namespace flap
