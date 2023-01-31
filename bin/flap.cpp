
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
    bool debug = false;
    app.add_flag("-d,--debug", debug, "Enable debug logs");

    app.add_option("source", source,
                   R"(Source file to compile or "-" for stdin)")
        ->required();
    CLI11_PARSE(app, argc, argv);

    auto doc = source == "-" ? flap::parse(std::cin) : flap::parse_file(source);
    if (debug) flap::set_log_stream(&std::cerr);
    auto consumer = flap::llvm::make_consumer();
    doc.root->accept(*consumer);
    std::cout << consumer->llvm_ir();
}

