#include <gtest/gtest.h>

#include <flap/ast/int_lit.hpp>

using flap::ast::IntLit;

TEST(IntLit, Radix) {
    const IntLit d{"100"};
    ASSERT_EQ(d.radix(), 10);
    static constexpr IntLit h{"0x100"};
    ASSERT_EQ(h.radix(), 16);
    static constexpr IntLit b{"0b100"};
    ASSERT_EQ(b.radix(), 2);
}

TEST(IntLit, Value) {
    constexpr IntLit d{"100"};
    ASSERT_EQ(d.value(), "100");

    constexpr IntLit h{"0x101"};
    ASSERT_EQ(h.value(), "101");

    constexpr IntLit b{"0b111"};
    ASSERT_EQ(b.value(), "111");
}
