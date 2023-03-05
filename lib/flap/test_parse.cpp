#include <gtest/gtest.h>

#include <flap/flap.hpp>
#include <flap/lex.hpp>

#include "flap/parser.hpp"

using flap::parse;
using flap::parse_chunk;
using flap::Parser;
using flap::StringView;
using Tok = flap::lex::Token;

namespace ast = flap::ast;

template <class F>
auto parse_and_check_end(StringView str, F&& f) {
    auto p = Parser(str);
    auto res = f(p);
    EXPECT_EQ(p.lexer().current().token, Tok::End);
    return res;
}

TEST(Expr, IntLitDec) {
    auto expr =
        parse_and_check_end("100", [](auto& p) { return p.parse_expr(); });
    ASSERT_TRUE(ast::is_int_lit(expr));
    const auto& i = ast::get_int_lit(expr);
    ASSERT_EQ(i.radix(), 10);
    ASSERT_EQ(i.value(), "100");
    ASSERT_EQ(i.raw_value(), "100");
}

TEST(Expr, IntLitHex) {
    auto expr =
        parse_and_check_end("0x55", [](auto& p) { return p.parse_expr(); });
    ASSERT_TRUE(ast::is_int_lit(expr));
    const auto& i = ast::get_int_lit(expr);

    ASSERT_EQ(i.radix(), 16);
    ASSERT_EQ(i.value(), "55");
    ASSERT_EQ(i.raw_value(), "0x55");
}

TEST(Expr, IntLitBin) {
    auto expr =
        parse_and_check_end("0b111", [](auto& p) { return p.parse_expr(); });
    ASSERT_TRUE(ast::is_int_lit(expr));
    const auto& i = ast::get_int_lit(expr);
    ASSERT_EQ(i.radix(), 2);
    ASSERT_EQ(i.value(), "111");
    ASSERT_EQ(i.raw_value(), "0b111");
}

TEST(Stmt, VarDef) {
    auto stmt = parse_and_check_end("i: i32 := 100",
                                    [](auto& p) { return p.parse_stmt(); });
    ASSERT_TRUE(ast::is_var_def(stmt));
    const auto& v = ast::get_var_def(stmt);
    ASSERT_EQ(v.name, "i");
    ASSERT_EQ(v.type, "i32");
    ASSERT_TRUE(ast::is_int_lit(v.expr));
    const auto& i = ast::get_int_lit(v.expr);
    ASSERT_EQ(i.value(), "100");
}

TEST(Func, Short) {
    auto res = parse_and_check_end("func: () -> i32 := 4",
                                   [](auto& p) { return p.parse_stmt(); });
    // auto res = parse_chunk("func: () -> i32 := 4");
    ASSERT_TRUE(ast::is_func(res));
    const auto& f = ast::get_func(res);
    ASSERT_EQ(f.name, "func");
    ASSERT_EQ(f.return_type, "i32");
    ASSERT_EQ(f.statements.size(), 1);
    ASSERT_TRUE(ast::is_ret_stmt(f.statements.at(0)));
}

TEST(Func, Long) {
    auto res = parse_and_check_end(R"(
    f: () -> i32 := {
        return 100
    }
    )",
                                   [](auto& p) { return p.parse_stmt(); });

    ASSERT_TRUE(ast::is_func(res));
    const auto& f = ast::get_func(res);
    ASSERT_EQ(f.name, "f");
    ASSERT_EQ(f.return_type, "i32");
    ASSERT_EQ(f.statements.size(), 1);
}

TEST(Func, IdenExpr) {
    auto res = parse_and_check_end(R"(
    f: () -> i32 := {
        var: i32 := 100
        return var
    }
    )",
                                   [](auto& p) { return p.parse_stmt(); });

    ASSERT_TRUE(ast::is_func(res));
    const auto& f = ast::get_func(res);
    ASSERT_EQ(f.name, "f");
    ASSERT_EQ(f.return_type, "i32");
    ASSERT_EQ(f.statements.size(), 2);
    ASSERT_TRUE(ast::is_var_def(f.statements.at(0)));
    ASSERT_TRUE(ast::is_ret_stmt(f.statements.at(1)));
}

// TEST(Func, Multiple) {
//     auto res = parse(R"(
//     a: () -> i32 := 4
//     b: () -> i32 := {
//         return 2;
//     }
//     )");
//     ASSERT_TRUE(res.root.functions->contains("a"));
// }
