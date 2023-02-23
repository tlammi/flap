#pragma once

#include <vector>

#include "flap/types/string_view.hpp"

namespace flap::lex {

enum class Token {
    Begin,   // Start of the document
    End,     // End of the document
    IntLit,  // Integer literal
};

struct Lexeme {
    Token token;
    StringView value;
};

constexpr bool operator==(const Lexeme& l, const Lexeme& r) {
    return l.token == r.token && l.value == r.value;
}

std::vector<Lexeme> lex(std::string_view str);
}  // namespace flap::lex
