#pragma once

#include <flap/consumer.hpp>
#include <memory>

namespace flap::llvm {

class Consumer : public ::flap::Consumer {};

std::unique_ptr<Consumer> make_consumer();
}  // namespace flap::llvm
