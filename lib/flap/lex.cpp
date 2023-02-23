#include "flap/lex.hpp"

namespace flap::lex {

using enum Token;

std::vector<Lexeme> lex(std::string_view str) {
    return {Lexeme{Begin, ""}, Lexeme{End, ""}};
}
}  // namespace flap::lex
