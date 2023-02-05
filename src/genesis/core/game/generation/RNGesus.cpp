#include "RNGesus.hpp"

#include "genesis/core/data/ColonistAttribs.hpp"
#include "genesis/core/game/entities/Colonist.hpp"
#include "genesis/core/game/World.hpp"
#include <random>

namespace genesis {

Species RNGesus::randSpecies(std::shared_ptr<Colonist> p1, std::shared_ptr<Colonist> p2) {
    if (p1 == nullptr && p2 == nullptr) {
        std::uniform_int_distribution<> d(0, SPECIES_NUM);
        return static_cast<Species>(d(_random::engine));
    } else {
        std::uniform_int_distribution<> d(1, 2);
        if (d(_random::engine) == 1) {
            return p1->genes.s;
        } else {
            return p2->genes.s;
        }
    }
}

std::shared_ptr<Colonist> RNGesus::generateColonist(
    std::shared_ptr<World> state,
    glm::vec3 pos,
    std::shared_ptr<Colonist> p1,
    std::shared_ptr<Colonist> p2
) {
    auto species = randSpecies(p1, p2);
    if (p1 == nullptr && p2 == nullptr) {
        std::uniform_int_distribution<> d(20, 30);
        return std::make_shared<Colonist>(
            ColonistGenes {
                species
            },
            "Name", // TODO
            pos,
            d(_random::engine)
        );
    } else if (p1 != nullptr && p2 != nullptr) {
        throw std::runtime_error("Not implemented");
    } else {
        throw std::runtime_error("Fucked family tree");
    }
}

}
