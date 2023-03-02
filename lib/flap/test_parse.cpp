#include <gtest/gtest.h>

#include <flap/flap.hpp>

using flap::parse;
namespace ast = flap::ast;

TEST(Expr, IntLit) {
    auto res = parse("100");
    ASSERT_TRUE(ast::is_int_lit(res.root));
}

