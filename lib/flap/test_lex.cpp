#include <gtest/gtest.h>

#include "flap/lex.hpp"

namespace lex = flap::lex;
TEST(Lex, Empty) {
    auto lexemes = lex::lex("");
    ASSERT_EQ(lexemes.size(), 2);
}

