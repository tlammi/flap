#pragma once

#include <flap/consumer.hpp>
#include <iostream>

namespace flap::lib::consumer {

class Debug final : public Consumer {
 public:
    void consume(const ast::Module& module_) override {
        std::cerr << "module\n";
    }
    void consume(const ast::Function& func) override {
        std::cerr << func.name() << ": () -> " << func.return_type() << '\n';
    }
    void consume(const ast::IntLiteral& lit) override {
        std::cerr << "integer literal: " << lit.value() << '\n';
    }
};
}  // namespace flap::lib::consumer
