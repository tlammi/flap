#pragma once

#include <flap/ast/function.hpp>
#include <flap/consumer.hpp>

#include "ast/scope.hpp"
namespace flap::ast {

class FunctionImpl final : public ::flap::ast::Function, public Scope {
 public:
    FunctionImpl(std::string_view name, std::string_view return_type)
        : m_name{name}, m_ret{return_type} {}

    void accept(Consumer& consumer) const {
        consumer.consume(*this);
        if (m_i_lit) m_i_lit->accept(consumer);
    }

    std::string_view return_type() const noexcept override { return m_ret; }
    std::string_view name() const noexcept override { return m_name; }

    void add_int_literal(std::unique_ptr<IntLiteral>&& i) override {
        m_i_lit = std::move(i);
    }

 private:
    std::string_view m_name;
    std::string_view m_ret;
    std::unique_ptr<IntLiteral> m_i_lit{};
};
}  // namespace flap::ast
