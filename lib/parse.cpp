#include <flap/parse.hpp>

#include "ast/function_impl.hpp"
#include "ast/int_literal.hpp"
#include "ast/module_impl.hpp"
#include "lex.hpp"

namespace flap {
namespace lib {
namespace {

class Parser {
 public:
    explicit Parser(std::string_view doc) : m_lexer{doc} {}

    std::unique_ptr<flap::ast::Ast> parse() {
        auto mod = std::make_unique<ast::ModuleImpl>();
        parse_primary(*mod);
        return mod;
    }

 private:
    /**
     * Start parsing from "root" of the document
     * */
    void parse_primary(ast::Scope& scope) {
        auto lexeme = m_lexer.next();
        m_stack.push_back(lexeme);
        using enum lex::Token;
        switch (lexeme.token) {
            case Identifier:
                parse_identifier(scope);
            case Eof:
                return;
            default:
                do_throw();
        }
    }

    void parse_identifier(ast::Scope& scope) {
        using enum lex::Token;
        auto lexeme = m_lexer.next();
        if (lexeme.token != Colon) do_throw();
        lexeme = m_lexer.next();
        if (lexeme.token != Paren) do_throw();
        lexeme = m_lexer.next();
        if (lexeme.token != ParenClose) do_throw();
        lexeme = m_lexer.next();
        if (lexeme.token != Arrow) do_throw();
        lexeme = m_lexer.next();
        if (lexeme.token != Identifier) do_throw();
        auto return_type = lexeme.value;
        lexeme = m_lexer.next();
        if (lexeme.token != Define) do_throw();
        lexeme = m_lexer.next();
        if (lexeme.token != IntLiteral) do_throw();
        auto func = std::make_unique<ast::FunctionImpl>(m_stack.back().value,
                                                        return_type);
        func->add_int_literal(std::make_unique<ast::IntLiteral>(lexeme.value));
        m_stack.clear();
        scope.add_function(std::move(func));
    }

    [[noreturn]] static void do_throw() {
        throw std::runtime_error("Unexpected token");
    }

    lex::Lexer m_lexer;
    std::vector<lex::Lexeme> m_stack{};
};
}  // namespace

std::unique_ptr<flap::ast::Ast> parse(std::string_view doc) {
    Parser p{doc};
    return p.parse();
}

}  // namespace lib
std::unique_ptr<flap::ast::Ast> parse(std::string_view doc) {
    return ::flap::lib::parse(doc);
}
}  // namespace flap
