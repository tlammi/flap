#include <flap/consumer.hpp>

namespace flap::lib::consumer {

class Llvm final : public Consumer {
 public:
    void consume(const ast::Module& module_) override {}
    void consume(const ast::Function& func) override{};
    void consume(const ast::IntLiteral& lit) override{};

 private:
};

}  // namespace flap::lib::consumer
