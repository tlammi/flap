#pragma once

#include <flap/types/string_view.hpp>
#include <ostream>
#include <vector>

#include "3rdparty/magic_enum.hpp"

namespace flap::lex {

enum class Token {
    Begin,       // Start of the document
    End,         // End of the document
    IntLit,      // Integer literal
    Paren,       // (
    ParenClose,  // )
    Colon,       // :
    InitOper,    // :=
    Iden,        // Identifier
};

struct Lexeme {
    Token token;
    StringView value;
};

constexpr auto operator==(const Lexeme& l, const Lexeme& r) -> bool {
    return l.token == r.token && l.value == r.value;
}

inline auto operator<<(std::ostream& s, Token tok) -> std::ostream& {
    s << magic_enum::enum_name(tok);
    return s;
}

inline auto operator<<(std::ostream& s, const Lexeme& lex) -> std::ostream& {
    s << "Lexeme{" << lex.token << ", \"" << lex.value << "\"}";
    return s;
}

class Lexer {
 public:
    Lexer() {}
    explicit Lexer(StringView str) : m_str{str} {}

    auto current() const noexcept -> Lexeme;

    auto next() -> Lexeme;

 private:
    StringView m_str{};
    Lexeme m_cur{Token::Begin, ""};
};

auto lex(std::string_view str) -> std::vector<Lexeme>;
}  // namespace flap::lex
