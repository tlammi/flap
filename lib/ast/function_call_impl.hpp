#pragma once

#include <flap/ast/function_call.hpp>
#include <flap/consumer.hpp>

namespace flap::ast {

class FunctionCallImpl final : public ::flap::ast::FunctionCall {
 public:
    explicit FunctionCallImpl(std::string_view name) : m_name{name} {}

    std::string_view name() const noexcept override { return m_name; }

    void accept(Consumer& consumer) const override { consumer.consume(*this); }

 private:
    std::string_view m_name{};
};
}  // namespace flap::ast
