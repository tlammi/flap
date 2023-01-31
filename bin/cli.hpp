#pragma once

#include <filesystem>
#include <string_view>
#include <vector>

namespace flapc::cli {

using FsPath = std::filesystem::path;

struct CliOpts {
    bool debug{false};
    bool from_stdin{false};
    std::vector<FsPath> files{};
};

CliOpts parse(int argc, char** argv);

}  // namespace flapc::cli
