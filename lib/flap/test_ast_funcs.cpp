#include <gtest/gtest.h>

#include <flap/flap.hpp>

namespace ast = flap::ast;

TEST(Expr, HoldsIntLit) {
    ast::Expr e{ast::IntLit{"100"}};
    ASSERT_TRUE(ast::is_int_lit(e));
}

TEST(Node, HoldsIntLit) {
    ast::Expr e{ast::IntLit{"100"}};
    ast::Node n{std::move(e)};
    ASSERT_TRUE(ast::is_int_lit(n));
}

TEST(Node, HoldsExpr) {
    ast::Expr e{ast::IntLit{"100"}};
    ast::Node n{std::move(e)};
    ASSERT_TRUE(ast::is_expr(n));
}

