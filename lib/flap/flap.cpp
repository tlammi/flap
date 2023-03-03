#include <flap/flap.hpp>

namespace flap {

Parsed::Parsed(std::string doc)
    : doc{std::move(doc)}, root{ast::Node{ast::IntLit{this->doc}}} {}

Parsed parse(std::string doc) { return Parsed(std::move(doc)); }
}  // namespace flap
