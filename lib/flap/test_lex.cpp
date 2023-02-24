#include <gtest/gtest.h>

#include "flap/lex.hpp"

namespace lex = flap::lex;
using Lex = lex::Lexeme;
using Tok = lex::Token;
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
    Lex first{Tok::IntLit, "1"};
    Lex second{Tok::IntLit, "2"};
    ASSERT_EQ(lexemes.at(1), first);
    ASSERT_EQ(lexemes.at(2), second);
}

TEST(Lex, Hex) {
    auto lexemes = lex::lex("0x1234");
    ASSERT_EQ(lexemes.size(), 3);
    const auto expected = Lex{Tok::IntLit, "0x1234"};
    ASSERT_EQ(lexemes.at(1), expected);
}

TEST(Lex, Paren) {
    auto lexemes = lex::lex("()");
    ASSERT_EQ(lexemes.size(), 4);
    Lex first{Tok::Paren, "("};
    Lex second{Tok::ParenClose, ")"};
    ASSERT_EQ(lexemes.at(1), first);
    ASSERT_EQ(lexemes.at(2), second);
}

TEST(Lex, Colon) {
    auto lexemes = lex::lex("::::::");
    ASSERT_EQ(lexemes.size(), 8);
    constexpr auto expected = Lex{Tok::Colon, ":"};
    ASSERT_EQ(lexemes.at(6), expected);
}

TEST(Lex, Iden) {
    auto lexemes = lex::lex("foobar");
    ASSERT_EQ(lexemes.size(), 3);
    const auto expected = Lex{Tok::Iden, "foobar"};
    ASSERT_EQ(lexemes.at(1), expected);
}

