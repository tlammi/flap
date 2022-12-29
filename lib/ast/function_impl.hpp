#pragma once

#include <flap/ast/function.hpp>
#include <flap/consumer.hpp>
namespace flap::lib::ast {

class FunctionImpl final : public ::flap::ast::Function {
 public:
    FunctionImpl(std::string_view name, std::string_view return_type)
        : m_name{name}, m_ret{return_type} {}

    void accept(Consumer& consumer) const { return consumer.consume(*this); }

    std::string_view return_type() const noexcept override { return m_ret; }
    std::string_view name() const noexcept override { return m_name; }

 private:
    std::string_view m_name;
    std::string_view m_ret;
};
}  // namespace flap::lib::ast
