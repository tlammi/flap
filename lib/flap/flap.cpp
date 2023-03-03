#include <flap/flap.hpp>

#include "flap/lex.hpp"

namespace flap {
namespace {

using Tok = lex::Token;
struct Parser {
    // entrypoint for the parsing
    ast::Node parse() {
        auto lexeme = lexer.next();
        if (lexeme.token == Tok::IntLit) {
            return {ast::IntLit{lexeme.value}};
        }
        if (lexeme.token == Tok::Iden) {
            auto iden = lexeme.value;
            if (lexer.next().token != Tok::Colon) throw std::runtime_error(":");
            auto type = lexer.next();
            if (type.token != Tok::Iden) throw std::runtime_error("type");
            if (lexer.next().token != Tok::InitOper)
                throw std::runtime_error(":=");
            auto expr = lexer.next();
            if (expr.token != Tok::IntLit) throw std::runtime_error("int lit");
            return {ast::VarDef{iden, type.value,
                                ast::Expr{ast::IntLit{expr.value}}}};
        }
        throw std::runtime_error("oh no");
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
