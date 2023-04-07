#include "genesis/core/data/DataLoader.hpp"
#include "genesis/rendering/Renderer.hpp"
#include "genesis/core/game/chunks/MapArea.hpp"

#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "stc/Environment.hpp"
#include "stc/FS.hpp"

#include <memory>

namespace genesis {

static std::vector<spdlog::sink_ptr> sinks = {
    std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
#ifndef GENESIS_DEBUG
    std::make_shared<spdlog::sinks::basic_file_sink_mt>(
#ifdef _WIN32
            (stc::getHome() / "AppData/Local/Temp/genesis.log").string()
#else
            "/tmp/genesis.log"
#endif
    ),
#endif
};

std::shared_ptr<spdlog::logger> Renderer::logger = std::make_shared<spdlog::logger>("renderer", sinks.begin(), sinks.end());
std::shared_ptr<spdlog::logger> MapArea::logger = std::make_shared<spdlog::logger>("map", sinks.begin(), sinks.end());
std::shared_ptr<spdlog::logger> DataLoader::logger = std::make_shared<spdlog::logger>("DataLoader", sinks.begin(), sinks.end());

}
