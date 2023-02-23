#include "flap/lex.hpp"

#include <cctype>
#include <optional>

namespace flap::lex {

using enum Token;
namespace {

bool is_dec(char c) { return c >= '0' && c <= '9'; }

void skip(std::string_view& view) {
    while (!view.empty() && std::isspace(view.at(0))) view.remove_prefix(1);
}

std::optional<Lexeme> lex_int(std::string_view& view) {
    size_t idx = 0;
    while (idx < view.size() && is_dec(view.at(idx))) ++idx;
    auto res = view.substr(0, idx);
    view.remove_prefix(idx);
    return Lexeme{IntLit, res};
}

}  // namespace

std::vector<Lexeme> lex(std::string_view str) {
    std::vector<Lexeme> out{};
    out.emplace_back(Begin, "");
    while (!str.empty()) {
        skip(str);
        if (auto val = lex_int(str)) out.emplace_back(*val);
    }
    out.emplace_back(End, "");
    return out;
}
}  // namespace flap::lex
