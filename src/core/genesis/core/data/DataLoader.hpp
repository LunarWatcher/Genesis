#pragma once

#include "genesis/game/Creature.hpp"
#include "genesis/game/Civilisation.hpp"

#include "nlohmann/json.hpp"
#include "spdlog/logger.h"

#include <stc/FS.hpp>

#include <fstream>
#include <string>
#include <string_view>
#include <thread>
#include <future>

namespace genesis {

class DataLoader {
private:
    static std::shared_ptr<spdlog::logger> logger;

    std::future<void> runner;
    std::atomic<std::string_view> currLoading;

    /**
     * Loads the info and stores its description in currLoading.
     * 
     * This will be used for more in the future, but for now, its use is
     * limited because adding use for it is wayyy into the future.
     */
    void checkInfoOrThrow(const fs::path& subdir);

    void loadSpecies(const fs::path& root);
    void loadCivilisations(const fs::path& root);

    void load(const fs::path& root, std::function<void(DataLoader*, const fs::path&)> callback);

public:
    std::map<std::string, CreatureInfo> creatures;
    std::map<std::string, Civilisation> civilisations;

    DataLoader();

    void loadDirectory(const fs::path& directory);
    bool isLoading() { return runner.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready; }
    std::string_view getDescription() {
        return currLoading.load();
    }
};

}
