#include "DataLoader.hpp"
#include "genesis/core/data/DataLoader.hpp"
#include "genesis/game/Species.hpp"

#include <filesystem>
#include <future>
#include <stc/FS.hpp>
#include <stdexcept>

namespace genesis {

DataLoader::DataLoader() {
    // TODO: figure out paths
    currLoading.store("Getting ready...");

    runner = std::async(std::launch::async, [&]() {
        try {
            loadDirectory("data");
        } catch (std::exception& e) {
            logger->error("An error occurred when loading: {}", e.what());
            throw;
        } catch (...) {
            logger->error("An unlisted error occurred when loading.");
            throw;
        }
    });
    
    logger->info("DataLoader thread started.");
}



void DataLoader::loadDirectory(const fs::path& directory) {
    load(directory / "species", &DataLoader::loadSpecies);

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
            // TODO: do something with the meta files
            // Might make more sense to do higher-level stuff and do fancy shit like checking
            // for incompatible mods.
            // Modding is a future me problem though, and fuck her :p
            continue;
        } else if (file.path().extension() != ".json") {
            continue;
        }
        logger->info("{}", file.path().string());

        callback(this, file.path());
    }
    logger->info("Done.");
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

    for (auto& speciesInfo : data) {
        auto speciesID = speciesInfo.at("_id").get<std::string>();
        if (this->creatures.contains(speciesID)) {
            throw std::runtime_error("Species ID " + speciesID + " already exists.");
        }
        std::shared_ptr<SpeciesInfo> obj = std::make_shared<SpeciesInfo>();
        speciesInfo.get_to(*obj);
        // insert saves an unnecessary allocation
        creatures.insert({speciesID, obj});

        // Some stuff down the line is going to need direct subspecies access. Realistically,
        // the subspecies trees aren't going to be big, but I don't see an immediate
        // disadvantage to doing this, soooooooo we're doing it :)
        for (auto& subspecies : obj->subspecies) {
            creatures.insert({subspecies->_id, obj});
        }

    }
}

}
