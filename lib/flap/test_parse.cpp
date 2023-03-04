#include <gtest/gtest.h>

#include <flap/flap.hpp>

#include "flap/parser.hpp"

using flap::parse;
using flap::parse_chunk;
using flap::Parser;
namespace ast = flap::ast;

TEST(Expr, IntLitDec) {
    auto expr = Parser("100").parse_expr();
    ASSERT_TRUE(ast::is_int_lit(expr));
    const auto& i = ast::get_int_lit(expr);
    ASSERT_EQ(i.radix(), 10);
    ASSERT_EQ(i.value(), "100");
    ASSERT_EQ(i.raw_value(), "100");
    /*
    auto res = parse_chunk("100");
    ASSERT_TRUE(ast::is_int_lit(res.root));
    const auto& i = ast::get_int_lit(res.root);
    ASSERT_EQ(i.radix(), 10);
    ASSERT_EQ(i.value(), "100");
    ASSERT_EQ(i.raw_value(), "100");
    */
}

TEST(Expr, IntLitHex) {
    auto res = parse_chunk("0x55");
    ASSERT_TRUE(ast::is_int_lit(res.root));
    const auto& i = ast::get_int_lit(res.root);
    ASSERT_EQ(i.radix(), 16);
    ASSERT_EQ(i.value(), "55");
    ASSERT_EQ(i.raw_value(), "0x55");
}

TEST(Expr, IntLitBin) {
    auto res = parse_chunk("0b111");
    ASSERT_TRUE(ast::is_int_lit(res.root));
    const auto& i = ast::get_int_lit(res.root);
    ASSERT_EQ(i.radix(), 2);
    ASSERT_EQ(i.value(), "111");
    ASSERT_EQ(i.raw_value(), "0b111");
}

TEST(Stmt, VarDef) {
    auto res = parse_chunk("i: i32 := 100");
    ASSERT_TRUE(ast::is_var_def(res.root));
    const auto& v = ast::get_var_def(res.root);
    ASSERT_EQ(v.name, "i");
    ASSERT_EQ(v.type, "i32");
    ASSERT_TRUE(ast::is_int_lit(v.expr));
    const auto& i = ast::get_int_lit(v.expr);
    ASSERT_EQ(i.value(), "100");
}

TEST(Func, Short) {
    auto res = parse_chunk("func: () -> i32 := 4");
    ASSERT_TRUE(ast::is_func(res.root));
    const auto& f = ast::get_func(res.root);
    ASSERT_EQ(f.name, "func");
    ASSERT_EQ(f.return_type, "i32");
    ASSERT_EQ(f.statements.size(), 1);
    ASSERT_TRUE(ast::is_ret_stmt(f.statements.at(0)));
}

TEST(Func, Long) {
    auto res = parse_chunk(R"(
    f: () -> i32 := {
        return 100
    }
    )");

    ASSERT_TRUE(ast::is_func(res.root));
    const auto& f = ast::get_func(res.root);
    ASSERT_EQ(f.name, "f");
    ASSERT_EQ(f.return_type, "i32");
    ASSERT_EQ(f.statements.size(), 1);
}

TEST(Func, IdenExpr) {
    auto res = parse_chunk(R"(
     f: () -> i32 := {
         var: i32 := 100
         return var
     }
     )");
    ASSERT_TRUE(ast::is_func(res.root));
    const auto& f = ast::get_func(res.root);
    ASSERT_EQ(f.name, "f");
    ASSERT_EQ(f.return_type, "i32");
    ASSERT_EQ(f.statements.size(), 2);
    ASSERT_TRUE(ast::is_var_def(f.statements.at(0)));
    ASSERT_TRUE(ast::is_ret_stmt(f.statements.at(1)));
}

TEST(Func, Multiple) {
    auto res = parse(R"(
    a: () -> i32 := 4
    b: () -> i32 := {
        return 2;
    }
    )");
    ASSERT_TRUE(res.root.functions->contains("a"));
}
