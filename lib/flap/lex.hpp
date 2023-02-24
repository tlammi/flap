#pragma once

#include <ostream>
#include <vector>

#include "flap/types/string_view.hpp"

namespace flap::lex {

enum class Token {
    Begin,       // Start of the document
    End,         // End of the document
    IntLit,      // Integer literal
    Paren,       // (
    ParenClose,  // )
};

struct Lexeme {
    Token token;
    StringView value;
};

constexpr bool operator==(const Lexeme& l, const Lexeme& r) {
    return l.token == r.token && l.value == r.value;
}

inline std::ostream& operator<<(std::ostream& s, const Lexeme& lex) {
    s << "Lexeme{" << lex.value << '}';
    return s;
}

std::vector<Lexeme> lex(std::string_view str);
}  // namespace flap::lex
