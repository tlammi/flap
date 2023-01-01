#pragma once

#include <string_view>
#include <vector>

namespace flap::lex {

enum class Token {
    Colon,             // :
    Paren,             // (
    ParenClose,        // )
    Brace,             // {
    BraceClose,        // }
    Bracket,           // [
    BracketClose,      // ]
    Define,            // :=
    Arrow,             // ->
    IntLiteral,        // 0 or 49 or 101 etc.
    Return,            // return
    CommentOneLine,    // //.*?\n
    CommentMultiLine,  // /\*.*?\*/
    Eol,               // End of line
    Eof,               // End of file
    Identifier,        // Identifiers like main, myvar, ...
};

struct Lexeme {
    Token token;
    std::string_view value;
};

class Lexer {
 public:
    Lexer() {}
    explicit Lexer(std::string_view data) : m_data{data} {}

    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;

    Lexer(Lexer&&) noexcept = default;
    Lexer& operator=(Lexer&&) noexcept = default;

    ~Lexer() = default;

    Lexeme next();

    Lexeme current() const noexcept;

    std::vector<Lexeme> lex_all();

 private:
    Lexeme next_impl();
    std::string_view m_data{};
    Lexeme m_current{};
};

}  // namespace flap::lex
