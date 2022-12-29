#include <flap/consumer.hpp>

#include "consumer/debug.hpp"
#include "consumer/llvm.hpp"

namespace flap {

std::unique_ptr<Consumer> llvm_consumer() {
    return std::make_unique<lib::consumer::Llvm>();
}

std::unique_ptr<Consumer> debug_consumer() {
    return std::make_unique<lib::consumer::Debug>();
}
}  // namespace flap
