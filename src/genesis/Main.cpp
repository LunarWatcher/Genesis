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
#ifdef _WIN32
    try {
#endif
    genesis::Renderer renderer;
    renderer.run();
#ifdef _WIN32
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    } catch (const char* e) {
        std::cerr << "Char exception caught: " << e << std::endl;
    } catch (const std::string& e) {
        std::cerr << "String exception caught: " << e << std::endl;
    }
#endif
}
