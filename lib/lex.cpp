#include "lex.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>

namespace flap::lib::lex {

template <Token T>
std::optional<Lexeme> lex_no_value(std::string_view& str,
                                   std::string_view prefix) {
    if (str.starts_with(prefix)) {
        str.remove_prefix(prefix.size());
        return Lexeme{T, ""};
    }
    return std::nullopt;
}

std::optional<Lexeme> lex_symbol(std::string_view& str) {
    std::cerr << str << '\n';
    if (str.empty()) return std::nullopt;
    const auto f = str.front();
    if ((f < 'A' || (f > 'Z' && f < 'a') || f > 'z') && f != '_')
        return std::nullopt;
    size_t idx = 1;

    while (str.size() > idx) {
        const auto c = str.at(idx);
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '_') {
            ++idx;
        } else {
            break;
        }
    }
    auto res = str.substr(0, idx);
    str.remove_prefix(idx);
    return Lexeme{Token::Symbol, res};
}

void skip(std::string_view& str) {
    while (str.starts_with(' ') || str.starts_with('\t') ||
           str.starts_with('\n'))
        str.remove_prefix(1);
}

struct Matcher {
    std::string_view data;

    template <class C>
    Matcher& incase(std::string_view prefix, C&& c) {
        return *this;
    }
};

#define LEX_NO_VALUE(prefix, token) \
    if (auto lex = lex_no_value<token>(m_data, prefix)) return *lex

Lexeme Lexer::next() {
    skip(m_data);
    using enum Token;
    if (m_data.empty()) return {Eof, ""};
    LEX_NO_VALUE(":=", Define);
    LEX_NO_VALUE(":", Colon);
    LEX_NO_VALUE("(", Paren);
    LEX_NO_VALUE(")", ParenClose);
    LEX_NO_VALUE("[", Bracket);
    LEX_NO_VALUE("]", BracketClose);
    LEX_NO_VALUE("{", Brace);
    LEX_NO_VALUE("}", BraceClose);
    LEX_NO_VALUE("->", Arrow);
    LEX_NO_VALUE("\n", Eol);
    if (auto lex = lex_symbol(m_data)) return *lex;
    std::cerr << m_data << '\n';
    throw std::runtime_error("asdfasf");
}

std::vector<Lexeme> Lexer::lex_all() {
    std::vector<Lexeme> out{};
    while (true) {
        auto l = next();
        out.push_back(l);
        if (l.token == Token::Eof) break;
    }
    return out;
}
}  // namespace flap::lib::lex
