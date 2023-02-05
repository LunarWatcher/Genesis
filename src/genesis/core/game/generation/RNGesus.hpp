#pragma once

#include "glm/vec3.hpp"

#include "genesis/core/data/ColonistAttribs.hpp"

#include <memory>
#include <random>

namespace genesis {

// Forward declarations, because this file is severely prone to forward declaration problems.
class Colonist;
class World;

namespace RNGesus {

namespace _random {

inline std::random_device dev;
inline std::default_random_engine engine(dev());

}


/**
 * Generates a new colonist.
 *
 * Takes the two parameters p1 and p2, which represents the parents. Either, both these have to be null,
 * or are null.
 *
 * If the parents are null, the colonist is treated as the first entry in the lineage, generating the "DNA"
 * at random. Otherwise, some genetic fuckery is performed on the parents. Reproduction is asexual, because
 * it's easier to implement, and saves me from having to implement the related social constructs, and saves
 * me from wanting to implement modern constructs (trans rights are human rights).
 *
 * Additionally, if parents are supplied, it's assumed the colonist is a newborn. Otherwise, they're given a
 * semi-random age between 20 and 30. Using child labour to establish a new colony isn't stonks :p
 *
 * Though I should probably define what age ranges actually count as kids. They're not humans, so they don't
 * necessarily _have_ to be 18 to be considered adults. Depending on the timescale, it could be 5. Real-life
 * canines are considered adults after between 8 months and 2 years (dogs are that entire age range, foxes
 * are generally after a year, wolves are generally after two), according to three trivial searches not
 * accounting for variations between species
 */
std::shared_ptr<Colonist> generateColonist(
    std::shared_ptr<World> state,
    glm::vec3 pos,
    std::shared_ptr<Colonist> p1 = nullptr,
    std::shared_ptr<Colonist> p2 = nullptr
);

/**
 * Returns a random species.
 *
 * Similarly to generateColonist, this takes two optional colonist parameters. If these are supplied,
 * one of their species is returned at random. Otherwise, a random species from the entire pool is returned.
 *
 */
Species randSpecies(std::shared_ptr<Colonist> p1 = nullptr,
                    std::shared_ptr<Colonist> p2 = nullptr);

}

}
