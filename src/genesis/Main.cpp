#include "genesis/rendering/Renderer.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/stdout_color_sinks.h"


void bootstrapLoggers() {
    auto stdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    auto logger = std::make_shared<spdlog::logger>("Logger");
    logger->debug("Debug");
    logger->warning("hi");


    spdlog::cfg::load_env_levels();
}

int main() {

    bootstrapLoggers();

    genesis::Renderer renderer;
    renderer.run();
}
