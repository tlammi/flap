#include <flap/ast/int_literal.hpp>
#include <flap/consumer.hpp>
namespace flap::ast {

void IntLiteral::accept(Consumer& consumer) const { consumer.consume(*this); }
}  // namespace flap::ast
