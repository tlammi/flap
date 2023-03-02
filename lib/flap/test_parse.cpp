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

TEST(Expr, IntLitHex) {}

