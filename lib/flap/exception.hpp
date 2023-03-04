#pragma once

#include <sstream>
#include <stdexcept>

#include "flap/lex.hpp"
namespace flap {
namespace detail {

inline std::string build_msg(lex::Lexeme actual) {
    std::stringstream ss{};
    ss << "Unexpected token: '" << actual.value << '\'';
    return ss.str();
}
}  // namespace detail

class Exception : public std::runtime_error {
 public:
    explicit Exception(const std::string& msg) : std::runtime_error(msg) {}
};

class UnexpectedToken : public Exception {
 public:
    UnexpectedToken(lex::Lexeme actual)
        : Exception(detail::build_msg(actual)) {}
};

}  // namespace flap
