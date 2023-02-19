#include "flap/lex.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace lex = flap::lex;

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
    ASSERT_THAT(tokens,
                testing::ElementsAre(Identifier, Colon, Paren, ParenClose,
                                     Arrow, Identifier, Eof));
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
    ASSERT_THAT(tokens, testing::ElementsAre(Identifier, Colon, Paren,
                                             ParenClose, Arrow, Identifier,
                                             Define, IntLiteral, Eof));
    auto strs = to_strs(lexemes);
    ASSERT_EQ(strs.at(0), "main");
    ASSERT_EQ(strs.at(5), "i32");
    ASSERT_EQ(strs.at(7), "42");
}

TEST(Comment, WithMain) {
    static constexpr std::string_view data = R"(
// this is a test comment
main: () -> i32 := 4

)";
    lex::Lexer l{data};
    auto lexemes = l.lex_all();
    auto tokens = to_tokens(lexemes);
    using enum lex::Token;
    ASSERT_THAT(tokens,
                testing::ElementsAre(CommentOneLine, Identifier, Colon, Paren,
                                     ParenClose, Arrow, Identifier, Define,
                                     IntLiteral, Eof));
}

TEST(Operator, Sum) {
    static constexpr std::string_view data = "1 + 2";
    lex::Lexer l{data};
    auto lexemes = l.lex_all();
    auto tokens = to_tokens(lexemes);
    using enum lex::Token;
    ASSERT_THAT(tokens,
                testing::ElementsAre(IntLiteral, Operator, IntLiteral, Eof));
    auto strs = to_strs(lexemes);
    ASSERT_EQ(strs.at(1), "+");
}

TEST(Operator, PrefixInc) {
    static constexpr std::string_view data = "++i";
    lex::Lexer l{data};
    auto oper = l.next();
    auto identifier = l.next();
    auto end = l.next();
    ASSERT_EQ(oper.token, lex::Token::Operator);
    ASSERT_EQ(identifier.token, lex::Token::Identifier);
    ASSERT_EQ(end.token, lex::Token::Eof);
    ASSERT_EQ(oper.value, "++");
}

TEST(Operator, SuffixDec) {
    static constexpr std::string_view data = "i--";

    lex::Lexer l{data};
    auto identifier = l.next();
    auto oper = l.next();
    auto end = l.next();
    ASSERT_EQ(oper.token, lex::Token::Operator);
    ASSERT_EQ(identifier.token, lex::Token::Identifier);
    ASSERT_EQ(end.token, lex::Token::Eof);
    ASSERT_EQ(oper.value, "--");
}

