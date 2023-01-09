#pragma once

#include <flap/ast/function.hpp>
#include <flap/ast/module.hpp>
#include <memory>
#include <vector>

namespace flap::ast {

class ModuleImpl : public Module {
 public:
    void accept(Consumer& consumer) const noexcept override;

    void add(std::unique_ptr<Ast>&& c) { m_children.push_back(std::move(c)); }

 private:
    std::vector<std::unique_ptr<Ast>> m_children{};
};
}  // namespace flap::ast
