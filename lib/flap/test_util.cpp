#include <gtest/gtest.h>

#include <flap/util.hpp>

using flap::match;

TEST(Match, Single) {
    std::variant<int> v{10};
    auto res = match(v, [](int i) { return i * 2; });
    ASSERT_EQ(res, 20);
}

TEST(Match, Multiple) {
    std::variant<int, long, short> v{30};
    auto res = match(v, [](auto i) -> int { return i * 2; });
    ASSERT_EQ(res, 60);
}

