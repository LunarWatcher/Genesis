#include "genesis/rendering/Renderer.hpp"

#include "stc/Environment.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/helpers.h"

#include <iostream>

void initializeLogging() {
    // Might as well wrap this to a default.
    std::string envVal = stc::getEnv("SPDLOG_LEVEL", "info");
    spdlog::cfg::helpers::load_levels(envVal);

    spdlog::set_pattern("[%^%l%$] %v");
}

int main() {
    genesis::Renderer renderer;
    renderer.run();
}
