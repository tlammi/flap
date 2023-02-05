#include <flap/ast/int_literal.hpp>
#include <flap/parse.hpp>
#include <fstream>
#include <map>
#include <optional>

#include "ast/binary_operator_impl.hpp"
#include "ast/function_call_impl.hpp"
#include "ast/function_impl.hpp"
#include "ast/function_param_impl.hpp"
#include "ast/identifier_expr_impl.hpp"
#include "ast/module_impl.hpp"
#include "ast/ret_stmt_impl.hpp"
#include "ast/var_def_stmt_impl.hpp"
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
            auto ptr = parse_primary();
            if (!ptr) continue;
            mod->add(std::move(ptr));
        }
        return mod;
    }

 private:
    /**
     * Start parsing from "root" of the document
     * */
    std::unique_ptr<ast::Ast> parse_primary() {
        // auto lexeme = m_lexer.next();
        using enum lex::Token;
        switch (m_lexer.current().token) {
            case Identifier:
                return parse_identifier();
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
                break;
            default:
                do_throw();
        }
        return nullptr;
    }

    std::unique_ptr<ast::Ast> parse_identifier() {
        using enum lex::Token;
        auto first_lexeme = m_lexer.current();
        auto lexeme = m_lexer.next();
        if (lexeme.token == Colon) {
            lexeme = m_lexer.next();
            if (lexeme.token != Paren) do_throw(Paren);
            lexeme = m_lexer.next();
            return parse_function(first_lexeme.value);
        }
        if (lexeme.token == Paren) {
            parse_function_pattern(m_funcs.at(first_lexeme.value));
            return nullptr;
        }
        do_throw();
    }

    void parse_function_pattern(ast::FunctionImpl* func) {
        //
    }

    std::unique_ptr<ast::Function> parse_function(std::string_view name) {
        using enum lex::Token;
        auto params = parse_function_params();
        auto lexeme = m_lexer.current();
        check_eq(ParenClose);
        lexeme = m_lexer.next();
        check_eq(Arrow);
        lexeme = m_lexer.next();
        check_eq(Identifier);
        auto return_type = lexeme.value;
        lexeme = m_lexer.next();
        check_eq(Define);
        lexeme = m_lexer.next();
        auto func = std::make_unique<ast::FunctionImpl>(name, return_type,
                                                        std::move(params));
        m_funcs[name] = func.get();
        if (lexeme.token != Brace) {
            func->add(parse_short_function_body());
            return std::move(func);
        }
        if (lexeme.token == Brace) {
            auto stmts = parse_long_function_body();
            for (auto&& s : stmts) {
                func->add(std::move(s));
            }
            return std::move(func);
        }
        do_throw();
    }

    std::vector<std::unique_ptr<ast::FunctionParam>> parse_function_params() {
        std::vector<std::unique_ptr<ast::FunctionParam>> out{};
        using enum lex::Token;
        auto lexeme = m_lexer.current();
        if (lexeme.token == ParenClose) return out;
        while (true) {
            if (lexeme.token != Identifier) do_throw(Identifier);
            auto name = lexeme.value;
            lexeme = m_lexer.next();
            if (lexeme.token != Colon) do_throw(Colon);
            lexeme = m_lexer.next();
            if (lexeme.token != Identifier) do_throw(Identifier);
            auto type = lexeme.value;
            lexeme = m_lexer.next();
            out.push_back(std::make_unique<ast::FunctionParamImpl>(name, type));
            if (lexeme.token == ParenClose) break;
            if (lexeme.token != Comma) do_throw(Comma);
            lexeme = m_lexer.next();
        }
        return out;
    }

    std::unique_ptr<ast::RetStmt> parse_short_function_body() {
        auto ret_stmt = std::make_unique<ast::RetStmtImpl>();
        ret_stmt->add(parse_expr());
        return std::move(ret_stmt);
    }

    std::vector<std::unique_ptr<ast::Stmt>> parse_long_function_body() {
        using enum lex::Token;
        std::vector<std::unique_ptr<ast::Stmt>> out{};
        m_lexer.next();  // eat {
        while (m_lexer.current().token != BraceClose) {
            out.push_back(parse_stmt());
        }
        m_lexer.next();  // eat }
        return out;
    }

    std::unique_ptr<ast::Stmt> parse_stmt() {
        using enum lex::Token;
        auto lexeme = m_lexer.current();
        if (lexeme.token == Return) {
            m_lexer.next();
            auto stmt = std::make_unique<ast::RetStmtImpl>();
            stmt->add(parse_expr());
            return stmt;
        }
        if (lexeme.token == Identifier) {
            const auto name = lexeme.value;
            lexeme = m_lexer.next();
            if (lexeme.token != Colon) do_throw();
            lexeme = m_lexer.next();
            if (lexeme.token != Identifier) do_throw();
            const auto type = lexeme.value;
            lexeme = m_lexer.next();
            if (lexeme.token != Define) do_throw();
            lexeme = m_lexer.next();
            auto res =
                std::make_unique<ast::VarDefStmtImpl>(name, type, parse_expr());
            return res;
        }
        do_throw();
    }

    std::unique_ptr<ast::Expr> parse_expr() {
        auto lhs = parse_expr_lhs();
        auto lexeme = m_lexer.current();
        if (lexeme.token != lex::Token::Operator) return lhs;
        return parse_expr_binop(std::move(lhs));
    }

    std::unique_ptr<ast::Expr> parse_expr_lhs() {
        auto lexeme = m_lexer.current();
        using enum lex::Token;
        if (lexeme.token == IntLiteral) {
            auto lit = std::make_unique<ast::IntLiteral>(lexeme.value);
            m_lexer.next();  // eat the literal
            return lit;
        }
        if (lexeme.token == Identifier) {
            auto next = m_lexer.next();
            if (next.token != Paren) {
                return std::make_unique<ast::IdentifierExprImpl>(lexeme.value);
            }
            m_lexer.next();  // eat (
            auto args = parse_function_args();
            next = m_lexer.current();
            if (next.token != ParenClose) do_throw(ParenClose);
            m_lexer.next();
            return std::make_unique<ast::FunctionCallImpl>(lexeme.value,
                                                           std::move(args));
        }
        do_throw();
    }

    std::vector<std::unique_ptr<ast::Expr>> parse_function_args() {
        using enum lex::Token;
        std::vector<std::unique_ptr<ast::Expr>> out{};
        auto lexeme = m_lexer.current();
        if (lexeme.token == ParenClose) return out;
        while (true) {
            out.push_back(parse_expr());
            lexeme = m_lexer.current();
            if (lexeme.token == lex::Token::ParenClose) break;
            if (lexeme.token == lex::Token::Comma) {
                m_lexer.next();
                // lexeme = m_lexer.next();
                continue;
            }
            do_throw();
        }
        return out;
    }

    std::unique_ptr<ast::Expr> parse_expr_binop(
        std::unique_ptr<ast::Expr> lhs) {
        auto lexeme = m_lexer.current();
        m_lexer.next();
        auto rhs = parse_expr_lhs();
        auto next = m_lexer.current();
        if (next.token == lex::Token::Operator) {
            lhs = std::make_unique<ast::BinaryOperatorImpl>(
                lexeme.value, std::move(lhs), std::move(rhs));
            return parse_expr_binop(std::move(lhs));
        }
        return std::make_unique<ast::BinaryOperatorImpl>(
            lexeme.value, std::move(lhs), std::move(rhs));
    }

    void check_eq(lex::Token tok) {
        if (m_lexer.current().token != tok) do_throw(tok);
    }

    [[noreturn]] void do_throw(
        std::optional<lex::Token> expected = std::nullopt) {
        std::stringstream ss;
        ss << "Unexpected token: " << m_lexer.current();
        if (expected) {
            ss << ", expected: " << *expected;
        }
        throw std::runtime_error(ss.str());
    }

    lex::Lexer m_lexer;
    std::map<std::string_view, ast::FunctionImpl*> m_funcs{};
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
