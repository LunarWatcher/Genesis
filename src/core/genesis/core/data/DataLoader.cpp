#include "DataLoader.hpp"
#include "genesis/core/data/DataLoader.hpp"
#include "genesis/game/Creature.hpp"

#include <filesystem>
#include <future>
#include <stc/FS.hpp>
#include <stdexcept>

namespace genesis {

DataLoader::DataLoader() {
    // TODO: figure out paths
    currLoading.store("Getting ready...");
    runner = std::async(std::launch::async, [&]() {
        loadDirectory("data");
    });
}



void DataLoader::loadDirectory(const fs::path& directory) {
    load(directory / "species", &DataLoader::loadSpecies);
    load(directory / "civilisations", &DataLoader::loadSpecies);

}

void DataLoader::load(const fs::path& subdir, std::function<void(DataLoader*, const fs::path&)> callback) {
    if (!fs::exists(subdir)) {
        logger->warn("{} doesn't exist. Skipping entry...", subdir.string());
        return;
    }
    logger->info("Loading {}...", subdir.string());

    for (auto& file : fs::directory_iterator(subdir)) {
        // This stuff is case-sensitive. It's fine for now, but isn't bullet proof
        // if this type of mod is eventually supported, 
        if (file.path().filename() == "info.json") {
            // Skip the meta files
            continue;
        } else if (file.path().extension() != ".json") {
            continue;
        }

        callback(this, file.path());
    }
}

void DataLoader::checkInfoOrThrow(const fs::path& subdir) {
    if (!fs::exists(subdir / "info.json")) {
        throw std::runtime_error("Failed to locate info file in " + subdir.string());
    }

    std::ifstream f(subdir / "info.json");
    auto json = nlohmann::json::parse(f);
    currLoading.store(json.at("description").get<std::string>());
}

void DataLoader::loadSpecies(const fs::path& root) {
    std::ifstream f(root);
    nlohmann::json data = nlohmann::json::parse(f);

    for (auto& [speciesID, speciesInfo] : data.items()) {
        if (this->creatures.contains(speciesID)) {
            throw std::runtime_error("Species ID " + speciesID + " already exists.");
        }
        auto obj = CreatureInfo{};
        speciesInfo.get_to(obj);
        obj._id = speciesID;

        // insert saves an unnecessary allocation
        creatures.insert({speciesID, obj});
    }
}

}
