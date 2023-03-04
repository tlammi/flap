#include <flap/flap.hpp>
#include <iostream>

#include "flap/algo.hpp"
#include "flap/exception.hpp"
#include "flap/lex.hpp"

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
            case Tok::IntLit:
                return {ast::IntLit{lexer.current().value}};
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
                auto expr = get(Tok::IntLit);
                return {ast::VarDef{iden.value, next.value,
                                    ast::Expr{ast::IntLit{expr.value}}}};
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
        // long func body
        if (lexer.next().token == Tok::Brace) {
            get(Tok::Ret);
            auto expr = get(Tok::IntLit);
            auto int_lit = ast::IntLit{expr.value};
            std::vector<ast::Stmt> statements{ast::RetStmt{std::move(int_lit)}};
            return ast::Func{name, ret_type, std::move(statements)};
        } else {
            std::cerr << lexer.current() << '\n';
            auto expr = lexer.current();
            auto int_lit = ast::IntLit{expr.value};
            std::vector<ast::Stmt> statements{ast::RetStmt{std::move(int_lit)}};
            return ast::Func{name, ret_type, std::move(statements)};
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
