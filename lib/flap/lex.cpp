#include "lex.hpp"

#include <iostream>
#include <magic_enum.hpp>
#include <optional>
#include <stdexcept>

#include "logs.hpp"

namespace flap::lex {

using namespace std::literals::string_view_literals;

std::ostream& operator<<(std::ostream& os, Token tok) {
    os << '"' << magic_enum::enum_name(tok) << '"';
    return os;
}
std::ostream& operator<<(std::ostream& os, Lexeme lexeme) {
    os << "(" << lexeme.token << ": \"" << lexeme.value << "\")";
    return os;
}

constexpr bool is_hex(char c) {
    const auto no = c >= '0' && c <= '9';
    const auto big = c >= 'A' && c <= 'Z';
    const auto small = c >= 'a' && c <= 'z';
    return no || big || small;
}

constexpr bool is_bin(char c) { return c == '1' || c == '0'; }
constexpr bool is_dec(char c) { return c >= '0' && c <= '9'; }

constexpr bool is_oper(char c) {
    return "+-*/<>^&%?!"sv.find(c) != std::string_view::npos;
}

template <Token T>
std::optional<Lexeme> lex_no_value(std::string_view& str,
                                   std::string_view prefix) {
    if (str.starts_with(prefix)) {
        str.remove_prefix(prefix.size());
        return Lexeme{T, ""};
    }
    return std::nullopt;
}

std::optional<Lexeme> lex_identifier(std::string_view& str) {
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
    return Lexeme{Token::Identifier, res};
}

std::optional<Lexeme> lex_int_literal(std::string_view& str) {
    size_t idx = 0;
    if (str.starts_with("0x")) {
        idx = 2;
        while (idx < str.size() && is_hex(str.at(idx))) ++idx;
    } else if (str.starts_with("0b")) {
        idx = 2;
        while (idx < str.size() && is_bin(str.at(idx))) ++idx;
    } else {
        while (idx < str.size() && is_dec(str.at(idx))) ++idx;
    }

    if (!idx) return std::nullopt;
    auto res = str.substr(0, idx);
    str.remove_prefix(idx);
    return Lexeme{Token::IntLiteral, res};
}

std::optional<Lexeme> lex_operator(std::string_view& str) {
    size_t idx = 0;
    while (idx < str.size() && is_oper(str.at(idx))) {
        ++idx;
    }
    if (!idx) return std::nullopt;
    auto res = str.substr(0, idx);
    str.remove_prefix(idx);
    return Lexeme{Token::Operator, res};
}

std::optional<Lexeme> lex_comment_one_line(std::string_view& str) {
    if (str.starts_with("//")) {
        size_t idx = 2;
        while (true) {
            idx = str.find("\n", idx);
            if (idx != std::string_view::npos) {
                auto match = str.substr(0, idx);
                str.remove_prefix(idx);
                return Lexeme{Token::CommentOneLine, match};
            }
        }
    }
    return std::nullopt;
}

std::optional<Lexeme> lex_comment_multi_line(std::string_view& str) {
    if (str.starts_with("/*")) {
        auto idx = str.find("*/", 2);
        if (idx != std::string_view::npos) {
            idx = idx + 2;
            auto match = str.substr(0, idx);
            str.remove_prefix(idx);
            return Lexeme{Token::CommentMultiLine, match};
        }
    }
    return std::nullopt;
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

Lexeme Lexer::next() {
    m_current = next_impl();
    DEBUG << "lexed: " << m_current;
    return m_current;
}

Lexeme Lexer::current() const noexcept { return m_current; }

#define LEX_NO_VALUE(prefix, token) \
    if (auto lex = lex_no_value<token>(m_data, prefix)) return *lex

Lexeme Lexer::next_impl() {
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
    LEX_NO_VALUE(",", Comma);
    LEX_NO_VALUE("->", Arrow);
    LEX_NO_VALUE("\n", Eol);
    LEX_NO_VALUE("return", Return);
    if (auto lex = lex_comment_one_line(m_data)) return *lex;
    if (auto lex = lex_comment_multi_line(m_data)) return *lex;
    if (auto lex = lex_identifier(m_data)) return *lex;
    if (auto lex = lex_int_literal(m_data)) return *lex;
    if (auto lex = lex_operator(m_data)) return *lex;
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
}  // namespace flap::lex
