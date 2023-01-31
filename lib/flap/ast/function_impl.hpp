#pragma once

#include <flap/ast/function.hpp>
#include <flap/consumer.hpp>
#include <vector>

namespace flap::ast {

class FunctionImpl final : public ::flap::ast::Function {
 public:
    FunctionImpl(std::string_view name, std::string_view return_type,
                 std::vector<std::unique_ptr<ast::FunctionParam>> params)
        : m_name{name}, m_ret{return_type}, m_params{std::move(params)} {}

    void accept(Consumer& consumer) const {
        auto recurse = consumer.consume(*this);
        if (recurse == Recurse::Yes)
            for (const auto& s : m_stmts) s->accept(consumer);
    }

    std::string_view return_type() const noexcept override { return m_ret; }
    std::string_view name() const noexcept override { return m_name; }

    std::vector<const ast::FunctionParam*> params() const override {
        std::vector<const ast::FunctionParam*> out{};
        out.reserve(m_params.size());
        for (const auto& p : m_params) {
            out.push_back(p.get());
        }
        return out;
    }

    void add(std::unique_ptr<Stmt>&& s) { m_stmts.push_back(std::move(s)); }
    std::vector<const ast::Ast*> statements() const override {
        std::vector<const Ast*> out{};
        for (const auto& stmt : m_stmts) {
            out.push_back(stmt.get());
        }
        return out;
    }

    std::vector<const Pattern*> patterns() const override {
        std::vector<const Pattern*> out{};
        out.reserve(m_pats.size());
        for (const auto& p : m_pats) {
            out.push_back(p.get());
        }
        return out;
    }

    void add_pattern(std::unique_ptr<Pattern> pattern) {
        m_pats.push_back(std::move(pattern));
    }

 private:
    std::string_view m_name;
    std::string_view m_ret;
    std::vector<std::unique_ptr<ast::FunctionParam>> m_params{};
    std::vector<std::unique_ptr<Stmt>> m_stmts{};
    std::vector<std::unique_ptr<Pattern>> m_pats{};
};
}  // namespace flap::ast
