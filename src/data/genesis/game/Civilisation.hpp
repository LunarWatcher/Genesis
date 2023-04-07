#pragma once

#include "Creature.hpp"
#include "genesis/game/Creature.hpp"

namespace genesis {

struct Civilisation {
    std::string name;
    std::string plural;
    std::string adjective;

    std::vector<std::string> species;

};

}
