#pragma once

#include "genesis/game/Species.hpp"
#include "glm/vec3.hpp"

#include <memory>
#include <random>

namespace genesis {

// Forward declarations, because this file is severely prone to forward declaration problems.

class World;
class GameCreature;

namespace RNGesus {

namespace _random {

inline std::random_device dev;
inline std::mt19937 engine(dev());

}

/**
 * @param p1                The first parent. Optional if baby is false
 * @param p2                The second parent. Optional if baby is false
 * @param baby              Whether or not the newly generated creature is a baby.
 *                          Requires p1 != nullptr && p2 != nullptr.
 * @param overrideSpecies   Forces a specific species. Primarily intended for early-game generation, but
 *                          could presumably be used for some god complex story line or whatever.
 *
 *                          Ngl though, if I implement high-level story logic, this does make for a lot of
 *                          interesting shit.
 *
 * @returns             A new randomly generated creature
 * @throws              std::runtime_error if any of the parameter configurations
 *                      mentioned in the params are used.
 */
extern std::shared_ptr<GameCreature> genCreature(
    std::shared_ptr<GameCreature> p1,
    std::shared_ptr<GameCreature> p2,
    bool baby,
    std::shared_ptr<SpeciesInfo> overrideSpecies
);

}

namespace util {
// I'm sure this will backfire wonderfully some day, and I look forward to future me roasting me for being stupid :)
using namespace RNGesus;

extern int randInt(int min, int max);

}

}
