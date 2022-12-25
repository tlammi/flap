#pragma once

#include <variant>

namespace flap {
class Consumer;
namespace ast {

class Ast {
 public:
    virtual ~Ast() {}
    virtual void accept(Consumer& c) const = 0;
};

}  // namespace ast
}  // namespace flap

