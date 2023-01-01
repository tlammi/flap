#pragma once

#include <flap/ast/function.hpp>
#include <flap/consumer.hpp>
#include <vector>

#include "ast/scope.hpp"

namespace flap::ast {

class FunctionImpl final : public ::flap::ast::Function, public StmtScope {
 public:
    FunctionImpl(std::string_view name, std::string_view return_type)
        : m_name{name}, m_ret{return_type} {}

    void accept(Consumer& consumer) const {
        consumer.consume(*this);
        for (const auto& s : m_stmts) s->accept(consumer);
    }

    std::string_view return_type() const noexcept override { return m_ret; }
    std::string_view name() const noexcept override { return m_name; }

    void add(std::unique_ptr<Stmt>&& s) override {
        m_stmts.push_back(std::move(s));
    }

 private:
    std::string_view m_name;
    std::string_view m_ret;
    std::vector<std::unique_ptr<Stmt>> m_stmts{};
};
}  // namespace flap::ast
