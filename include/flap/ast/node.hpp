#pragma once

#include <flap/ast/int_lit.hpp>
#include <variant>
namespace flap::ast {

class Node {
 public:
    using Var = std::variant<IntLit>;

    template <class... Ts>
    constexpr explicit Node(Ts&&... ts) : m_var{std::forward<Ts>(ts)...} {}

    operator Var&() & { return m_var; }
    operator const Var&() const& { return m_var; }

    constexpr bool is_int_lit() const noexcept {
        return std::holds_alternative<IntLit>(m_var);
    }

 private:
    Var m_var;
};
}  // namespace flap::ast
