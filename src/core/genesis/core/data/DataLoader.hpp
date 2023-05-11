#pragma once

#include "genesis/game/Species.hpp"

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

    void load(const fs::path& root, std::function<void(DataLoader*, const fs::path&)> callback);

public:
    // Contains the full species tree, including subspecies
    std::map<std::string, std::shared_ptr<SpeciesInfo>> creatures;

    DataLoader();

    void loadDirectory(const fs::path& directory);
    bool isLoading() {
        bool v = runner.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready;
        if (!v) {
            runner.get();
        }
        return v;
    }
    std::string_view getDescription() {
        return currLoading.load();
    }
};

}
