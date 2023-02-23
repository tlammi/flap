#pragma once

#include <vector>

#include "flap/types/string_view.hpp"

namespace flap::lex {

enum class Token {
    Begin,  // Start of the document
    End,    // End of the document
};

struct Lexeme {
    Token token;
    StringView value;
};

std::vector<Lexeme> lex(std::string_view str);
}  // namespace flap::lex
