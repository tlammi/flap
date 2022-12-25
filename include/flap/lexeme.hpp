#pragma once

#include <flap/token.hpp>
#include <string_view>

namespace flap {

struct Lexeme {
    Token token;
    std::string_view value;
};

}  // namespace flap
