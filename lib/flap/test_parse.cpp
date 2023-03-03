#include <gtest/gtest.h>

#include <flap/flap.hpp>

using flap::parse;
namespace ast = flap::ast;

TEST(Expr, IntLitDec) {
    auto res = parse("100");
    ASSERT_TRUE(ast::is_int_lit(res.root));
    const auto& i = ast::get_int_lit(res.root);
    ASSERT_EQ(i.radix(), 10);
    ASSERT_EQ(i.value(), "100");
    ASSERT_EQ(i.raw_value(), "100");
}

TEST(Expr, IntLitHex) {
    auto res = parse("0x55");
    ASSERT_TRUE(ast::is_int_lit(res.root));
    const auto& i = ast::get_int_lit(res.root);
    ASSERT_EQ(i.radix(), 16);
    ASSERT_EQ(i.value(), "55");
    ASSERT_EQ(i.raw_value(), "0x55");
}

TEST(Expr, IntLitBin) {
    auto res = parse("0b111");
    ASSERT_TRUE(ast::is_int_lit(res.root));
    const auto& i = ast::get_int_lit(res.root);
    ASSERT_EQ(i.radix(), 2);
    ASSERT_EQ(i.value(), "111");
    ASSERT_EQ(i.raw_value(), "0b111");
}

TEST(Stmt, VarDef) {
    auto res = parse("i: i32 := 100");
    ASSERT_TRUE(ast::is_var_def(res.root));
    const auto& v = ast::get_var_def(res.root);
    ASSERT_EQ(v.name, "i");
    ASSERT_EQ(v.type, "i32");
    ASSERT_TRUE(ast::is_int_lit(v.expr));
    const auto& i = ast::get_int_lit(v.expr);
    ASSERT_EQ(i.value(), "100");
}

TEST(Func, OneLine) {
    auto res = parse("func: () -> i32 := 4");
    ASSERT_TRUE(ast::is_func(res.root));
    const auto& f = ast::get_func(res.root);
    ASSERT_EQ(f.name, "func");
    ASSERT_EQ(f.return_type, "i32");
    ASSERT_EQ(f.statements.size(), 1);
    ASSERT_TRUE(ast::is_ret_stmt(f.statements.at(0)));
}
