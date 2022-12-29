
#include <flap/flap.hpp>
#include <iostream>

int main() {
    auto ast = flap::parse("main: () -> i32 := 42");
    auto consumer = flap::debug_consumer();
    ast->accept(*consumer);
}

