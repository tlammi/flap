
#include <flap/flap.hpp>
#include <iostream>
#include <string_view>

using namespace std::literals::string_view_literals;

int main(int argc, char** argv) {
    auto ast = flap::parse("main: () -> i32 := 42");
    std::unique_ptr<flap::Consumer> consumer{};
    if (argc < 2 || argv[1] == "--debug"sv)
        consumer = flap::debug_consumer();
    else if (argv[1] == "--llvm"sv)
        consumer = flap::llvm_consumer();
    else
        throw std::runtime_error("Invalid usage");
    ast->accept(*consumer);
}

