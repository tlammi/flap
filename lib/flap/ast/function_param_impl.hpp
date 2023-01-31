#pragma once

#include <flap/ast/function_param.hpp>
namespace flap::ast {

class FunctionParamImpl final : public FunctionParam {
 public:
    FunctionParamImpl(std::string_view name, std::string_view type)
        : m_name{name}, m_type{type} {}

    std::string_view name() const noexcept override { return m_name; }
    std::string_view type() const noexcept override { return m_name; }

    void accept(Consumer& consumer) const override { consumer.consume(*this); }

 private:
    std::string_view m_name;
    std::string_view m_type;
};

}  // namespace flap::ast
