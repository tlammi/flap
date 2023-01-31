#include "cli.hpp"

#include <CLI/App.hpp>
#include <CLI/Config.hpp>
#include <CLI/Formatter.hpp>

namespace flapc::cli {

CliOpts parse(int argc, char** argv) {
    CliOpts opts{};
    CLI::App app{"flap compiler"};
    app.add_flag("-d,--debug", opts.debug, "Verbose");
    app.add_option("files", opts.files, "Input files");
    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError& e) {
        ::exit(app.exit(e));
    }
    return opts;
}

}  // namespace flapc::cli
