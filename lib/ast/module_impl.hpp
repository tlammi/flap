#pragma once

#include <flap/ast/function.hpp>
#include <flap/ast/module.hpp>
#include <memory>
#include <vector>

#include "ast/ast_priv.hpp"

namespace flap::lib::ast {

class ModuleImpl : public ::flap::ast::Module, public AstPriv {
 public:
    void accept(Consumer& consumer) const noexcept override;

    void add_function(std::unique_ptr<flap::ast::Function>&& f) override {
        m_funcs.push_back(std::move(f));
    }

 private:
    std::vector<std::unique_ptr<flap::ast::Function>> m_funcs{};
};
}  // namespace flap::lib::ast
