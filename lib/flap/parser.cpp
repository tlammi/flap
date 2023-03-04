#include "flap/parser.hpp"

#include "flap/exception.hpp"
namespace flap {
namespace {

[[noreturn]] auto wrong_lex(lex::Lexeme lexeme) -> void {
    throw UnexpectedToken(lexeme);
}
}  // namespace

using Tok = lex::Token;

ast::Expr Parser::parse_expr() {
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
auto Parser::get(Tok tok) -> lex::Lexeme {
    auto res = m_lex.next();
    if (res.token != tok) wrong_lex(res);
    return res;
}
}  // namespace flap
