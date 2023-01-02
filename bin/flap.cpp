
#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <flap/debug/consumer.hpp>
#include <flap/flap.hpp>
#include <flap/llvm/consumer.hpp>
#include <iostream>
#include <string_view>

using namespace std::literals::string_view_literals;

int main(int argc, char** argv) {
    CLI::App app{"flap compiler"};
    std::string backend{"debug"};
    std::filesystem::path source{};
    app.add_option("-b,--backend", backend,
                   R"(Backend to use. "debug" or "llvm")");

    app.add_option("source", source,
                   R"(Source file to compile or "-" for stdin)")
        ->required();
    CLI11_PARSE(app, argc, argv);
    std::unique_ptr<flap::Consumer> consumer{};
    if (backend == "debug")
        consumer = flap::debug::make_consumer();
    else if (backend == "llvm")
        consumer = flap::llvm::make_consumer();
    else
        throw std::runtime_error("Invalid consumer");

    auto doc = source == "-" ? flap::parse(std::cin) : flap::parse_file(source);
    doc.root->accept(*consumer);
}

