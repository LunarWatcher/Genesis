#include "genesis/Context.hpp"
#include "genesis/rendering/Renderer.hpp"

#include "stc/Environment.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/helpers.h"

#include <iostream>
#include "genesis/core/splash/Splash.hpp"

const bool genesis::Constants::isTest = false;

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
    auto& ctx = genesis::Context::getInstance();
    ctx.initRendererDeps();

    ctx.renderer->transition(std::make_shared<genesis::SplashScene>());
    ctx.renderer->run();
#ifdef _WIN32
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    } catch (const char* e) {
        std::cerr << "Char exception caught: " << e << std::endl;
    } catch (const std::string& e) {
        std::cerr << "String exception caught: " << e << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception type thrown" << std::endl;
    }
#endif
}
