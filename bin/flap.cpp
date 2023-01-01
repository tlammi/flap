
#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>
#include <flap/flap.hpp>
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

    auto consumer =
        backend == "debug" ? flap::debug_consumer() : flap::llvm_consumer();
    auto doc = source == "-" ? flap::parse(std::cin) : flap::parse_file(source);

    doc.root->accept(*consumer);
}

