#include <gtest/gtest.h>

#include <flap/flap.hpp>

namespace ast = flap::ast;

TEST(Expr, HoldsIntLit) {
    ast::Expr e{ast::IntLit{"100"}};
    ASSERT_TRUE(ast::is_int_lit(e));
}

TEST(Chunk, HoldsIntLit) {
    ast::Expr e{ast::IntLit{"100"}};
    ast::Chunk n{std::move(e)};
    ASSERT_TRUE(ast::is_int_lit(n));
}

TEST(Chunk, HoldsExpr) {
    ast::Expr e{ast::IntLit{"100"}};
    ast::Chunk n{std::move(e)};
    ASSERT_TRUE(ast::is_expr(n));
}

TEST(Expr, GetInt) {
    ast::Expr e{ast::IntLit{"1"}};
    const auto& i = get_int_lit(e);
    ASSERT_EQ(i.value(), "1");
}

TEST(Chunk, GetInt) {
    ast::Expr e{ast::IntLit{"1"}};
    ast::Chunk n{std::move(e)};
    const auto& i = get_int_lit(n);
    ASSERT_EQ(i.value(), "1");
}
