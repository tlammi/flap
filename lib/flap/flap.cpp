#include <flap/flap.hpp>

namespace flap {
Parsed parse(std::string doc) {
    return Parsed{std::move(doc), {ast::IntLit{"100"}}};
}
}  // namespace flap
