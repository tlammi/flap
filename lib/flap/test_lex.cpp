#include <gtest/gtest.h>

#include "flap/lex.hpp"

namespace lex = flap::lex;
TEST(Lex, Empty) {
    auto lexemes = lex::lex("");
    ASSERT_EQ(lexemes.size(), 2);
}

TEST(Lex, Int) {
    auto lexemes = lex::lex("100");
    ASSERT_EQ(lexemes.size(), 3);
    ASSERT_EQ(lexemes.at(1).value, "100");
}

TEST(Lex, MultiInt) {
    auto lexemes = lex::lex("1 2");
    ASSERT_EQ(lexemes.size(), 4);
    lex::Lexeme first{lex::Token::IntLit, "1"};
    lex::Lexeme second{lex::Token::IntLit, "2"};
    ASSERT_EQ(lexemes.at(1), first);
    ASSERT_EQ(lexemes.at(2), second);
}

TEST(Lex, Hex) {
    auto lexemes = lex::lex("0x1234");
    ASSERT_EQ(lexemes.size(), 3);
}

