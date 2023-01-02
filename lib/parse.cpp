#include <flap/ast/int_literal.hpp>
#include <flap/parse.hpp>
#include <fstream>

#include "ast/function_call_impl.hpp"
#include "ast/function_impl.hpp"
#include "ast/module_impl.hpp"
#include "ast/ret_stmt_impl.hpp"
#include "lex.hpp"
#include "logs.hpp"

namespace flap {
namespace {

class Parser {
 public:
    explicit Parser(std::string_view doc) : m_lexer{doc} {}

    std::unique_ptr<flap::ast::Ast> parse() {
        auto mod = std::make_unique<ast::ModuleImpl>();
        m_lexer.next();
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
        // auto lexeme = m_lexer.next();
        using enum lex::Token;
        switch (m_lexer.current().token) {
            case Identifier:
                parse_identifier(scope);
                break;
            case CommentOneLine:
                m_lexer.next();
                break;
            case CommentMultiLine:
                m_lexer.next();
                break;
            case Eol:
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
        auto func = std::make_unique<ast::FunctionImpl>(first_lexeme.value,
                                                        return_type);
        if (lexeme.token != Brace) {
            parse_short_function_body(*func);
            scope.add(std::move(func));
            return;
        }
        if (lexeme.token == Brace) {
            parse_long_function_body(*func);
            scope.add(std::move(func));
            return;
        }
        do_throw();
    }

    void parse_short_function_body(ast::StmtScope& scope) {
        auto ret_stmt = std::make_unique<ast::RetStmtImpl>();
        parse_expr(*ret_stmt);
        scope.add(std::move(ret_stmt));
    }

    void parse_long_function_body(ast::StmtScope& scope) {
        using enum lex::Token;
        m_lexer.next();  // eat {
        while (m_lexer.current().token != BraceClose) {
            parse_stmt(scope);
        }
        m_lexer.next();  // eat }
    }

    void parse_stmt(ast::StmtScope& scope) {
        using enum lex::Token;
        auto lexeme = m_lexer.current();
        if (lexeme.token == Return) {
            m_lexer.next();
            auto stmt = std::make_unique<ast::RetStmtImpl>();
            parse_expr(*stmt);
            scope.add(std::move(stmt));
            return;
        }
        do_throw();
    }

    void parse_expr(ast::ExprScope& scope) {
        auto lexeme = m_lexer.current();
        using enum lex::Token;
        if (lexeme.token == IntLiteral) {
            auto lit = std::make_unique<ast::IntLiteral>(lexeme.value);
            scope.add(std::move(lit));
            m_lexer.next();  // eat the literal
            return;
        }
        if (lexeme.token == Identifier) {
            auto next = m_lexer.next();
            if (next.token != Paren) do_throw();
            next = m_lexer.next();
            if (next.token != ParenClose) do_throw();
            scope.add(std::make_unique<ast::FunctionCallImpl>(lexeme.value));
            m_lexer.next();
            return;
        }
        do_throw();
    }

    [[noreturn]] void do_throw() {
        std::stringstream ss;
        ss << "Unexpected token: " << (int)m_lexer.current().token << ": "
           << m_lexer.current().value;
        throw std::runtime_error(ss.str());
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
