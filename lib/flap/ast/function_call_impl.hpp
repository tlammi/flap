#pragma once

#include <flap/ast/function_call.hpp>
#include <flap/consumer.hpp>

namespace flap::ast {

class FunctionCallImpl final : public ::flap::ast::FunctionCall {
 public:
    explicit FunctionCallImpl(std::string_view name,
                              std::vector<std::unique_ptr<ast::Expr>> args = {})
        : m_name{name}, m_args{std::move(args)} {}

    std::string_view name() const noexcept override { return m_name; }

    std::vector<const ast::Expr*> args() const override {
        std::vector<const ast::Expr*> out{};
        out.reserve(m_args.size());
        for (const auto& a : m_args) {
            out.push_back(a.get());
        }
        return out;
    }

    void accept(Consumer& consumer) const override {
        auto recurse = consumer.consume(*this);
        if (recurse == Recurse::Yes) {
            for (const auto& a : m_args) {
                a->accept(consumer);
            }
        }
    }

 private:
    std::string_view m_name{};
    std::vector<std::unique_ptr<ast::Expr>> m_args{};
};
}  // namespace flap::ast
