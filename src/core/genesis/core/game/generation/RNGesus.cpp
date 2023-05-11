#include "RNGesus.hpp"

#include "genesis/core/game/World.hpp"
#include "genesis/game/Species.hpp"
#include <memory>
#include <random>

namespace genesis {

std::shared_ptr<GameCreature> RNGesus::genCreature(
    std::shared_ptr<GameCreature> p1,
    std::shared_ptr<GameCreature> p2,
    bool baby,
    std::shared_ptr<SpeciesInfo> overrideSpecies
) {
    if (baby) {
        if (p1 == nullptr || p2 == nullptr) {
            // A
            throw std::runtime_error("Babies need known parents");
        }
        throw std::runtime_error("TODO");
    } else {
        if ((p1 == nullptr && p2 != nullptr) || (p1 != nullptr && p2 == nullptr)) {
            throw std::runtime_error("Can't have just one parent (yet?)");
        } else if (p1 == nullptr && p2 == nullptr) {
            // Primarily reserved for early-game generation for the time being.
            // Even with history (future me problem), there has to be a first somewhere in the chain.
            // This is the initial generation.
            // At the time of writing, this is used for the colony bootstrap rather than history bootstrap
            if (overrideSpecies == nullptr) {
                throw std::runtime_error("No history generation requires overrideSpecies");
            }

            // This is nasty
            
            auto speciesBase = overrideSpecies;
            if (overrideSpecies->subspecies.size() != 0) {
                // Subspecies implies the parent species cannot be used directly.
                
                // Pick random species
                speciesBase = overrideSpecies->subspecies.at(
                    std::uniform_int_distribution<size_t>(0, overrideSpecies->subspecies.size() - 1)(_random::engine)
                );
            }


            return std::make_shared<GameCreature>(
                *speciesBase,
                "Livi",
                "Destroyer of Worlds",
                std::uniform_int_distribution<unsigned int>(18, 30)(_random::engine)
            );
        } else {
            throw std::runtime_error("TODO");
        }
    }
}

}
