#include "flap/lex.hpp"

#include <cctype>
#include <optional>

#include "flap/exception.hpp"

namespace flap::lex {

using enum Token;
namespace {

constexpr bool lower_case(char c) { return c >= 'a' && c <= 'z'; }
constexpr bool upper_case(char c) { return c >= 'A' && c <= 'Z'; }
constexpr bool number(char c) { return c >= '0' && c <= '9'; }

constexpr bool iden_begin(char c) {
    return lower_case(c) || upper_case(c) || c == '_';
}
constexpr bool iden_body(char c) { return iden_begin(c) || number(c); }

constexpr bool is_dec(char c) { return c >= '0' && c <= '9'; }

constexpr bool is_hex(char c) {
    return number(c) || upper_case(c) || lower_case(c);
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}

void skip(std::string_view& view) {
    while (!view.empty() && std::isspace(view.at(0))) view.remove_prefix(1);
}

std::optional<Lexeme> lex_int(std::string_view& view) {
    size_t idx = 0;
    if (view.starts_with("0x")) {
        idx = 2;
        while (idx < view.size() && is_hex(view.at(idx))) ++idx;
        if (idx == 2) return std::nullopt;
        auto res = view.substr(0, idx);
        view.remove_prefix(idx);
        return Lexeme{IntLit, res};
    }
    while (idx < view.size() && is_dec(view.at(idx))) ++idx;
    if (idx == 0) return std::nullopt;
    auto res = view.substr(0, idx);
    view.remove_prefix(idx);
    return Lexeme{IntLit, res};
}

std::optional<Lexeme> lex_char(std::string_view& view, char c, Token tok) {
    if (view.front() == c) {
        auto res = view.substr(0, 1);
        view.remove_prefix(1);
        return Lexeme{tok, res};
    }
    return std::nullopt;
}
#define LEX_CHAR(c, tok) \
    if (auto val = lex_char(str, c, tok)) return *val;

std::optional<Lexeme> lex_iden(std::string_view& view) {
    size_t idx = 0;
    if (iden_begin(view.at(idx))) {
        ++idx;
        while (idx < view.size() && iden_body(view.at(idx))) ++idx;
        auto res = view.substr(0, idx);
        view.remove_prefix(idx);
        return Lexeme{Iden, res};
    }
    return std::nullopt;
}

Lexeme lex_next(std::string_view& str) {
    skip(str);
    if (str.empty()) return {End, ""};
    if (auto val = lex_int(str)) return *val;
    LEX_CHAR('(', Paren);
    LEX_CHAR(')', ParenClose);
    if (auto val = lex_iden(str)) return *val;
    throw Exception("Lexing error");
}

}  // namespace

std::vector<Lexeme> lex(std::string_view str) {
    std::vector<Lexeme> out{};
    out.emplace_back(Begin, "");
    while (true) {
        out.emplace_back(lex_next(str));
        if (out.back().token == End) break;
    }
    return out;
}
}  // namespace flap::lex
