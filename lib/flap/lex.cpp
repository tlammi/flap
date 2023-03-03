#include "flap/lex.hpp"

#include <cctype>
#include <optional>

#include "flap/exception.hpp"

namespace flap::lex {

using enum Token;
namespace {

constexpr auto lower_case(char c) -> bool { return c >= 'a' && c <= 'z'; }
constexpr auto upper_case(char c) -> bool { return c >= 'A' && c <= 'Z'; }
constexpr auto number(char c) -> bool { return c >= '0' && c <= '9'; }

constexpr auto iden_begin(char c) -> bool {
    return lower_case(c) || upper_case(c) || c == '_';
}
constexpr auto iden_body(char c) -> bool { return iden_begin(c) || number(c); }

constexpr auto is_dec(char c) -> bool { return c >= '0' && c <= '9'; }

constexpr auto is_hex(char c) -> bool {
    return number(c) || upper_case(c) || lower_case(c);
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}
constexpr auto is_bin(char c) -> bool { return c == '0' || c == '1'; }

auto skip(std::string_view& view) {
    while (!view.empty() && std::isspace(view.at(0))) view.remove_prefix(1);
}

auto lex_int(std::string_view& view) -> std::optional<Lexeme> {
    size_t idx = 0;
    if (view.starts_with("0x")) {
        idx = 2;
        while (idx < view.size() && is_hex(view.at(idx))) ++idx;
        if (idx == 2) return std::nullopt;
        auto res = view.substr(0, idx);
        view.remove_prefix(idx);
        return Lexeme{IntLit, res};
    }
    if (view.starts_with("0b")) {
        idx = 2;
        while (idx < view.size() && is_bin(view.at(idx))) ++idx;
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

auto lex_char(std::string_view& view, char c, Token tok)
    -> std::optional<Lexeme> {
    if (view.front() == c) {
        auto res = view.substr(0, 1);
        view.remove_prefix(1);
        return Lexeme{tok, res};
    }
    return std::nullopt;
}

auto lex_str(std::string_view& view, std::string_view str, Token tok)
    -> std::optional<Lexeme> {
    if (view.starts_with(str)) {
        auto res = view.substr(0, str.size());
        view.remove_prefix(str.size());
        return Lexeme{tok, res};
    }
    return std::nullopt;
}

auto lex_iden(std::string_view& view) -> std::optional<Lexeme> {
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
// NOLINTNEXTLINE
#define LEX_CHAR(c, tok) \
    if (auto val = lex_char(str, c, tok)) return *val;

// NOLINTNEXTLINE
#define LEX_STR(prefix, tok) \
    if (auto val = lex_str(str, prefix, tok)) return *val;

auto lex_next(std::string_view& str) -> Lexeme {
    skip(str);
    if (str.empty()) return {End, ""};
    if (auto val = lex_int(str)) return *val;
    LEX_STR(":=", InitOper);
    LEX_STR("->", Arrow);
    LEX_CHAR('(', Paren);
    LEX_CHAR(')', ParenClose);
    LEX_CHAR(':', Colon);
    if (auto val = lex_iden(str)) return *val;
    throw Exception("Lexing error");
}

}  // namespace

auto Lexer::current() const noexcept -> Lexeme { return m_cur; }

auto Lexer::next() -> Lexeme {
    m_cur = lex_next(m_str);
    return m_cur;
}

auto lex(std::string_view str) -> std::vector<Lexeme> {
    std::vector<Lexeme> out{};
    out.push_back(Lexeme{Begin, ""});
    Lexer lexer{str};
    while (true) {
        out.emplace_back(lexer.next());
        if (out.back().token == End) break;
    }
    return out;
}
}  // namespace flap::lex
