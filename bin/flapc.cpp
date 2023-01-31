
#include <CLI/App.hpp>
#include <flap/debug/consumer.hpp>
#include <flap/flap.hpp>
#include <flap/llvm/consumer.hpp>
#include <iostream>
#include <string_view>

#include "cli.hpp"

using namespace std::literals::string_view_literals;

int main(int argc, char** argv) {
    auto opts = flapc::cli::parse(argc, argv);

    if (opts.debug) flap::set_log_stream(&std::cerr);
    auto consumer = flap::llvm::make_consumer();

    if (opts.from_stdin) {
        auto doc = flap::parse(std::cin);
        doc.root->accept(*consumer);
        std::cout << consumer->llvm_ir();
        return EXIT_SUCCESS;
    }

    for (const auto& file : opts.files) {
        auto doc = flap::parse_file(file);
        doc.root->accept(*consumer);
        std::cout << consumer->llvm_ir();
        return EXIT_SUCCESS;
    }
}

