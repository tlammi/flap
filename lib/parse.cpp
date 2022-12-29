#include <flap/parse.hpp>

#include "ast/module_impl.hpp"
#include "lex.hpp"

namespace flap {
namespace lib {
namespace {

class Parser {
 public:
    explicit Parser(std::string_view doc) : m_lexer{doc} {}

    std::unique_ptr<flap::ast::Ast> parse() {
        return std::make_unique<ast::ModuleImpl>();
    }

 private:
    lex::Lexer m_lexer;
    std::vector<lex::Lexeme> m_stack{};
};
}  // namespace

std::unique_ptr<flap::ast::Ast> parse(std::string_view doc) {
    Parser p{doc};
    return p.parse();
}

}  // namespace lib
std::unique_ptr<flap::ast::Ast> parse(std::string_view doc) {
    return ::flap::lib::parse(doc);
}
}  // namespace flap
