#pragma once

#include <flap/consumer.hpp>
#include <memory>

namespace flap::debug {

class Consumer : public ::flap::Consumer {};

std::unique_ptr<Consumer> make_consumer();

}  // namespace flap::debug
