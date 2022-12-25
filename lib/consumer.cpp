#include <flap/consumer.hpp>

#include "consumer/llvm.hpp"

namespace flap {

std::unique_ptr<Consumer> llvm_consumer() {
    return std::make_unique<lib::consumer::Llvm>();
}
}  // namespace flap
