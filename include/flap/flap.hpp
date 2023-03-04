#pragma once

#include <flap/ast/access.hpp>
#include <flap/ast/chunk.hpp>
#include <flap/ast/doc.hpp>
#include <flap/ast/func.hpp>
#include <string>
namespace flap {

template <class Root>
struct Parsed {
    explicit Parsed(std::string doc);
    ~Parsed() = default;

    Parsed(const Parsed&) = delete;
    Parsed& operator=(const Parsed&) = delete;

    Parsed(Parsed&&) noexcept = default;
    Parsed& operator=(Parsed&&) noexcept = default;

    std::string doc;
    Root root;
};

Parsed<ast::Doc> parse(std::string doc);
Parsed<ast::Chunk> parse_chunk(std::string doc);

}  // namespace flap
