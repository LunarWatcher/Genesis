#include "RNGesus.hpp"

#include "genesis/core/game/entities/Colonist.hpp"
#include "genesis/core/game/World.hpp"

namespace genesis {

std::shared_ptr<Colonist> RNGesus::generateColonist(
    std::shared_ptr<World> state,
    std::shared_ptr<Colonist> p1,
    std::shared_ptr<Colonist> p2
) {
    if (p1 == nullptr && p2 == nullptr) {
        // Shut the compiler up
        return nullptr;
    } else if (p1 != nullptr && p2 != nullptr) {
        throw std::runtime_error("Not implemented");
    } else {
        throw std::runtime_error("Fucked family tree");
    }
}

}
