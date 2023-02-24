#include <gtest/gtest.h>

#include <flap/flap.hpp>

using flap::parse;
TEST(Expr, IntLit) {
    auto res = parse("100");
    ASSERT_TRUE(res.root.is_int_lit());
}
