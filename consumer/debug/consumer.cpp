
#include <flap/consumer.hpp>
#include <iostream>

namespace flap::debug {

class ConsumerImpl final : public Consumer {
    using R = Recurse;

 public:
    Recurse consume(const ast::Module& module_) override {
        std::cerr << "module\n";
        return R::Yes;
    }
    Recurse consume(const ast::Function& func) override {
        std::cerr << func.name() << ": () -> " << func.return_type() << '\n';
        return R::Yes;
    }
    Recurse consume(const ast::FunctionCall& call) override {
        std::cerr << "function call: " << call.name() << '\n';
        return R::Yes;
    }
    Recurse consume(const ast::IntLiteral& lit) override {
        std::cerr << "integer literal: " << lit.value() << '\n';
        return R::Yes;
    }
};

std::unique_ptr<Consumer> make_consumer() {
    return std::make_unique<ConsumerImpl>();
}
}  // namespace flap::debug
