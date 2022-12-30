#pragma once

#include <memory>
#include <vector>

#include "ast/function.hpp"
#include "ast/module.hpp"
#include "ast/scope.hpp"

namespace flap::lib::ast {

class ModuleImpl : public Module, public Scope {
 public:
    void accept(Consumer& consumer) const noexcept override;

    void add_function(std::unique_ptr<flap::ast::Function>&& f) override {
        m_funcs.push_back(std::move(f));
    }

 private:
    std::vector<std::unique_ptr<Function>> m_funcs{};
};
}  // namespace flap::lib::ast
