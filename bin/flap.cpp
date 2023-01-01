
#include <flap/flap.hpp>
#include <iostream>
#include <string_view>

using namespace std::literals::string_view_literals;

int main(int argc, char** argv) {
    std::unique_ptr<flap::ast::Ast> ast{};
    std::unique_ptr<flap::Consumer> consumer{};
    std::string data{};
    if (argc < 2 || argv[1] == "--debug"sv) {
        consumer = flap::debug_consumer();
        ast = flap::parse_view("main: () -> i32 := {return 42}");
    } else if (argv[1] == "--llvm"sv) {
        consumer = flap::llvm_consumer();
        ast = flap::parse_view("main: () -> i32 := {return 42}");
    } else {
        consumer = flap::llvm_consumer();
        auto [data_, ast_] = flap::parse_file(argv[1]);
        data = std::move(data_);
        ast = std::move(ast_);
    }
    ast->accept(*consumer);
}

