#pragma once

#include <flap/ast/expr.hpp>
#include <flap/ast/func.hpp>
#include <flap/ast/stmt.hpp>

#include "flap/lex.hpp"

namespace flap {

class Parser {
 public:
    explicit Parser(lex::Lexer lexer) : m_lex{std::move(lexer)} {
        // Dump Begin
        m_lex.next();
    }
    explicit Parser(StringView view) : Parser(lex::Lexer{view}) {}

    auto parse_expr() -> ast::Expr;
    auto parse_stmt() -> ast::Stmt;

    auto parse_func_body(StringView name, StringView return_type) -> ast::Func;

    auto lexer() const noexcept -> const lex::Lexer&;

 private:
    lex::Lexer m_lex;
    auto get(lex::Token tok) -> lex::Lexeme;
};
}  // namespace flap
