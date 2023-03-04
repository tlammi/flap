#include <flap/flap.hpp>

#include "flap/algo.hpp"
#include "flap/exception.hpp"
#include "flap/lex.hpp"
#include "flap/types/scope.hpp"

namespace flap {
namespace {

[[noreturn]] auto wrong_lex(lex::Lexeme actual) -> void {
    throw UnexpectedToken(actual);
}

using Tok = lex::Token;
struct Parser {
    // entrypoint for the parsing
    ast::Node parse() {
        auto lexeme = lexer.next();
        if (any_of_eq(lexeme.token, Tok::IntLit)) {
            return parse_expr();
        }
        if (lexeme.token == Tok::Iden) {
            return parse_from_iden();
        }
        wrong_lex(lexeme);
    }

    ast::Expr parse_expr() {
        switch (lexer.current().token) {
            case Tok::IntLit: {
                auto cur = lexer.current();
                lexer.next();
                return {ast::IntLit{cur.value}};
            }
            case Tok::Iden: {
                auto iden = lexer.current();
                lexer.next();
                return ast::IdenExpr{iden.value};
            }
            default:
                wrong_lex(lexer.current());
        }
    }

    ast::Node parse_from_iden() {
        auto iden = lexer.current();
        get(Tok::Colon);
        auto next = lexer.next();
        switch (next.token) {
            case Tok::Iden: {
                get(Tok::InitOper);
                lexer.next();
                return {ast::VarDef{iden.value, next.value, parse_expr()}};
            }
            case Tok::Paren: {
                get(Tok::ParenClose);
                get(Tok::Arrow);
                auto ret_type = get(Tok::Iden);
                get(Tok::InitOper);
                return parse_func_body(iden.value, ret_type.value);
            }
            default:
                wrong_lex(next);
        }
    }

    ast::Func parse_func_body(StringView name, StringView ret_type) {
        if (lexer.next().token == Tok::Brace) {
            // long func body
            std::vector<ast::Stmt> statements{};
            lexer.next();
            while (lexer.current().token != Tok::BraceClose) {
                statements.push_back(parse_stmt());
            }
            return ast::Func{name, ret_type, std::move(statements)};
        } else {
            std::vector<ast::Stmt> statements{ast::RetStmt{parse_expr()}};
            return ast::Func{name, ret_type, std::move(statements)};
        }
    }

    ast::Stmt parse_stmt() {
        // auto lexeme = lexer.next();
        auto lexeme = lexer.current();
        switch (lexeme.token) {
            case Tok::Ret: {
                lexer.next();
                return ast::RetStmt{parse_expr()};
            }
            case Tok::Iden: {
                get(Tok::Colon);
                auto type = get(Tok::Iden);
                get(Tok::InitOper);
                lexer.next();
                return ast::VarDef{lexeme.value, type.value, parse_expr()};
            }
            default:
                wrong_lex(lexeme);
        }
    }

    lex::Lexeme get(Tok tok) {
        auto res = lexer.next();
        if (res.token != tok) wrong_lex(res);
        return res;
    }

    lex::Lexer lexer;
};

ast::Node do_parse(StringView doc) {
    Parser p{lex::Lexer{doc}};
    return p.parse();
}
}  // namespace

Parsed::Parsed(std::string doc)
    : doc{std::move(doc)}, root{do_parse(this->doc)} {}

Parsed parse(std::string doc) { return Parsed(std::move(doc)); }
}  // namespace flap
