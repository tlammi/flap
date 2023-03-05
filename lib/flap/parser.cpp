#include "flap/parser.hpp"

#include "flap/exception.hpp"
namespace flap {
namespace {

[[noreturn]] auto wrong_lex(lex::Lexeme lexeme) -> void {
    throw UnexpectedToken(lexeme);
}
}  // namespace

using Tok = lex::Token;

auto Parser::parse_expr() -> ast::Expr {
    switch (m_lex.current().token) {
        case Tok::IntLit: {
            auto cur = m_lex.current();
            m_lex.next();
            return ast::IntLit{cur.value};
        }
        default:
            wrong_lex(m_lex.current());
    }
}

auto Parser::parse_stmt() -> ast::Stmt {
    auto lexeme = m_lex.current();
    switch (lexeme.token) {
        case Tok::Ret: {
            m_lex.next();
            return ast::RetStmt{parse_expr()};
        }
        case Tok::Iden: {
            get(Tok::Colon);
            auto lexeme2 = m_lex.next();
            switch (lexeme2.token) {
                case Tok::Iden:
                    get(Tok::InitOper);
                    m_lex.next();
                    return ast::VarDef{lexeme.value, lexeme2.value,
                                       parse_expr()};
                case Tok::Paren: {
                    get(Tok::ParenClose);
                    get(Tok::Arrow);
                    auto type = m_lex.next();
                    get(Tok::InitOper);
                    m_lex.next();
                    return parse_func_body(lexeme.value, type.value);
                }
                default:
                    wrong_lex(lexeme2);
            }
        }
        default:
            wrong_lex(lexeme);
    }
}
auto Parser::parse_func_body(StringView name, StringView return_type)
    -> ast::Func {
    std::vector<ast::Stmt> statements{ast::RetStmt{parse_expr()}};
    return ast::Func{name, return_type, std::move(statements)};
}

auto Parser::lexer() const noexcept -> const lex::Lexer& { return m_lex; }

auto Parser::get(Tok tok) -> lex::Lexeme {
    auto res = m_lex.next();
    if (res.token != tok) wrong_lex(res);
    return res;
}
}  // namespace flap
