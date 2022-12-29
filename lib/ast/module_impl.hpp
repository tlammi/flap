#pragma once

#include <flap/ast/module.hpp>

namespace flap::lib::ast {

class ModuleImpl : public ::flap::ast::Module {
 public:
    void accept(Consumer& consumer) const noexcept override;

 private:
};
}  // namespace flap::lib::ast
