#include <gtest/gtest.h>

#include "util.hpp"

using namespace flap::util;

enum class Enum {
    A,
    B,
    COUNT_,
};

TEST(EnumArr, Simple) {
    constexpr EnumArr<Enum, int> ea{};
    static_assert(ea.size() == underlying_cast(Enum::COUNT_));
}

TEST(EnumArr, Func) {
    using enum Enum;
    auto ea = make_enum_arr<Enum, int (*)(int)>(
        A, [](int i) { return i * 2; }, B, [](int i) { return i * 3; });
    ASSERT_EQ(ea[A](1), 2);
    ASSERT_EQ(ea[B](2), 6);
}
