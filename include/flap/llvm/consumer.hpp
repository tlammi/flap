#pragma once

#include <flap/consumer.hpp>
#include <memory>

namespace flap::llvm {

class Consumer : public ::flap::Consumer {
 public:
    /*
     * Access LLVM IR after the parsing has been done
     * */
    virtual std::string llvm_ir() = 0;
};

std::unique_ptr<Consumer> make_consumer();
}  // namespace flap::llvm
