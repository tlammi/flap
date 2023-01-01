#include <flap/ast/int_literal.hpp>
#include <flap/parse.hpp>
#include <fstream>

#include "ast/function_impl.hpp"
#include "ast/module_impl.hpp"
#include "ast/ret_stmt_impl.hpp"
#include "lex.hpp"

namespace flap {
namespace {

class Parser {
 public:
    explicit Parser(std::string_view doc) : m_lexer{doc} {}

    std::unique_ptr<flap::ast::Ast> parse() {
        auto mod = std::make_unique<ast::ModuleImpl>();
        while (m_lexer.current().token != lex::Token::Eof) {
            parse_primary(*mod);
        }
        return mod;
    }

 private:
    /**
     * Start parsing from "root" of the document
     * */
    void parse_primary(ast::FunctionScope& scope) {
        auto lexeme = m_lexer.next();
        using enum lex::Token;
        switch (lexeme.token) {
            case Identifier:
                parse_identifier(scope);
            case CommentOneLine:
                break;
            case CommentMultiLine:
                break;
            case Eof:
                return;
            default:
                do_throw();
        }
    }

    void parse_identifier(ast::FunctionScope& scope) {
        using enum lex::Token;
        auto first_lexeme = m_lexer.current();
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
        if (lexeme.token == IntLiteral) {
            auto func = std::make_unique<ast::FunctionImpl>(first_lexeme.value,
                                                            return_type);
            auto ret = std::make_unique<ast::RetStmtImpl>();
            ret->add(std::make_unique<ast::IntLiteral>(lexeme.value));
            func->add(std::move(ret));
            scope.add(std::move(func));
            return;
        }
        if (lexeme.token == Brace) {
            lexeme = m_lexer.next();
            if (lexeme.token != Return) do_throw();
            lexeme = m_lexer.next();
            if (lexeme.token != IntLiteral) do_throw();
            auto func = std::make_unique<ast::FunctionImpl>(first_lexeme.value,
                                                            return_type);
            auto ret = std::make_unique<ast::RetStmtImpl>();
            ret->add(std::make_unique<ast::IntLiteral>(lexeme.value));
            func->add(std::move(ret));
            scope.add(std::move(func));
            lexeme = m_lexer.next();
            if (lexeme.token != BraceClose) do_throw();
            return;
        }
        do_throw();
    }

    [[noreturn]] static void do_throw() {
        throw std::runtime_error("Unexpected token");
    }

    lex::Lexer m_lexer;
};
}  // namespace

std::unique_ptr<ast::Ast> parse_view(std::string_view doc) {
    Parser p{doc};
    return p.parse();
}
Doc parse(std::istream& s) {
    std::istreambuf_iterator<char> begin{s};
    std::istreambuf_iterator<char> end{};
    std::string doc{begin, end};
    auto ast = parse_view(doc);
    return {std::move(doc), std::move(ast)};
}
Doc parse_file(const std::filesystem::path& path) {
    std::ifstream fs{path};
    return parse(fs);
}

}  // namespace flap
