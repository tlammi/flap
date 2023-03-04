#pragma once

#include <sstream>
#include <stdexcept>

#include "flap/lex.hpp"
namespace flap {
namespace detail {

template <class... Ts>
auto merge_strs(Ts&&... ts) -> std::string {
    std::stringstream ss{};
    (ss << ... << std::forward<Ts>(ts));
    return ss.str();
}

inline std::string build_msg(lex::Lexeme actual) {
    std::stringstream ss{};
    ss << "Unexpected token: '" << actual.value << '\'';
    return ss.str();
}
}  // namespace detail

class Exception : public std::runtime_error {
 public:
    template <class... Ts>
    explicit Exception(Ts&&... ts)
        : std::runtime_error(detail::merge_strs(std::forward<Ts>(ts)...)) {}
};

class UnexpectedToken : public Exception {
 public:
    UnexpectedToken(lex::Lexeme actual)
        : Exception(detail::build_msg(actual)) {}
};

}  // namespace flap
