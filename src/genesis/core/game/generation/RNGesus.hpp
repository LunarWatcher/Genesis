#pragma once

#include <memory>

namespace genesis {

// Forward declarations, because this file is severely prone to forward declaration problems.
class Colonist;
class World;

namespace RNGesus {

/**
 * Generates a new colonist.
 *
 * Takes the two parameters p1 and p2, which represents the parents. Either, both these have to be null,
 * or are null.
 *
 * If the parents are null, the colonist is treated as the first entry in the lineage, generating the "DNA"
 * at random. Otherwise, some genetic fuckery is performed on the parents. 
 *
 * Additionally, if parents are supplied, it's assumed the colonist is a newborn. Otherwise, they're given a
 * semi-random age between 20 and 30. Using child labour to establish a new colony isn't stonks :p
 */
std::shared_ptr<Colonist> generateColonist(
    std::shared_ptr<World> state,
    std::shared_ptr<Colonist> p1,
    std::shared_ptr<Colonist> p2
);

}

}
