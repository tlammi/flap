#include "lex.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace lex = flap::lib::lex;

std::vector<lex::Token> to_tokens(const std::vector<lex::Lexeme>& lexemes) {
    std::vector<lex::Token> tokens{};
    tokens.reserve(lexemes.size());
    for (const auto [token, value] : lexemes) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<std::string_view> to_strs(const std::vector<lex::Lexeme>& lexemes) {
    std::vector<std::string_view> strs{};
    strs.reserve(lexemes.size());
    for (const auto [token, value] : lexemes) {
        strs.push_back(value);
    }
    return strs;
}

TEST(Function, Declaration) {
    static constexpr std::string_view data = "main: () -> i32";
    lex::Lexer l{data};
    auto lexemes = l.lex_all();
    auto tokens = to_tokens(lexemes);
    using enum lex::Token;
    ASSERT_THAT(tokens, testing::ElementsAre(Symbol, Colon, Paren, ParenClose,
                                             Arrow, Symbol, Eof));
    auto strs = to_strs(lexemes);
    ASSERT_EQ(strs.at(0), "main");
    ASSERT_EQ(strs.at(5), "i32");
}

TEST(Function, OneLineDefinition) {
    static constexpr std::string_view data = "main: () -> i32 := 42";
    lex::Lexer l{data};
    auto lexemes = l.lex_all();
    auto tokens = to_tokens(lexemes);
    using enum lex::Token;
    ASSERT_THAT(tokens,
                testing::ElementsAre(Symbol, Colon, Paren, ParenClose, Arrow,
                                     Symbol, Define, IntLiteral, Eof));
}

