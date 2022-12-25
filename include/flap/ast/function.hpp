#pragma once

#include <flap/ast/ast.hpp>
#include <string_view>

namespace flap::ast {

class Function final : public Ast {
 public:
    void accept(Consumer& c) const override;

    std::string_view return_type() const noexcept;
    std::string_view name() const noexcept;
};
}  // namespace flap::ast
