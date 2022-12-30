#pragma once

#include <flap/ast/function.hpp>
#include <flap/ast/module.hpp>
#include <memory>
#include <vector>

#include "ast/scope.hpp"

namespace flap::ast {

class ModuleImpl : public Module, public Scope {
 public:
    void accept(Consumer& consumer) const noexcept override;

    void add_function(std::unique_ptr<flap::ast::Function>&& f) override {
        m_funcs.push_back(std::move(f));
    }

 private:
    std::vector<std::unique_ptr<Function>> m_funcs{};
};
}  // namespace flap::ast
