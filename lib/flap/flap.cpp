#include <flap/flap.hpp>

#include "flap/algo.hpp"
#include "flap/exception.hpp"
#include "flap/lex.hpp"
#include "flap/logs.hpp"
#include "flap/types/scope.hpp"

namespace flap {
namespace {

[[noreturn]] auto wrong_lex(lex::Lexeme actual) -> void {
    throw UnexpectedToken(actual);
}

using Tok = lex::Token;
struct Parser {
    ast::Chunk parse_chunk() {
        // Skip Begin token
        auto lexeme = lexer.next();
        if (any_of_eq(lexeme.token, Tok::IntLit)) {
            return parse_expr();
        }
        if (lexeme.token == Tok::Iden) {
            return parse_from_iden();
        }
        wrong_lex(lexeme);
    }

    ast::Doc parse() {
        ast::Doc doc{};
        // Skip Begin token
        lexer.next();
        while (true) {
            switch (lexer.current().token) {
                case Tok::End:
                    return doc;
                case Tok::Iden: {
                    auto stmt = parse_from_iden();
                    if (ast::is_func(stmt)) {
                        auto f = ast::get_func(std::move(stmt));
                        logs::debug("parse: found func: ", f.name);
                        doc.functions->insert(f.name, std::move(f));
                    }
                }
                default: {
                }
            }
            lexer.next();
        }
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

    ast::Stmt parse_from_iden() {
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

ast::Doc do_parse(StringView doc) {
    Parser p{lex::Lexer{doc}};
    return p.parse();
}

ast::Chunk do_parse_chunk(StringView doc) {
    Parser p{lex::Lexer{doc}};
    return p.parse_chunk();
}
}  // namespace

template <>
Parsed<ast::Doc>::Parsed(std::string doc)
    : doc{std::move(doc)}, root{do_parse(this->doc)} {}

template <>
Parsed<ast::Chunk>::Parsed(std::string doc)
    : doc{std::move(doc)}, root{do_parse_chunk(this->doc)} {}

Parsed<ast::Doc> parse(std::string doc) {
    return Parsed<ast::Doc>{std::move(doc)};
}
Parsed<ast::Chunk> parse_chunk(std::string doc) {
    return Parsed<ast::Chunk>(std::move(doc));
}
}  // namespace flap
