#pragma once

#include <flap/ast/expr.hpp>

#include "flap/lex.hpp"

namespace flap {

class Parser {
 public:
    explicit Parser(lex::Lexer lexer) : m_lex{std::move(lexer)} {
        // Dump Begin
        m_lex.next();
    }
    explicit Parser(StringView view) : Parser(lex::Lexer{view}) {}

    ast::Expr parse_expr();

 private:
    lex::Lexer m_lex;
    auto get(lex::Token tok) -> lex::Lexeme;
};
}  // namespace flap
