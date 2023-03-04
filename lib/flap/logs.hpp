#pragma once

#include <iostream>

namespace flap::logs {

template <class... Ts>
void debug(Ts&&... ts) {
    (std::cerr << ... << ts) << '\n';
}
}  // namespace flap::logs
