#include "GameEntity.hpp"

namespace genesis {


GameEntity::GameEntity(
    CreatureInfo& speciesBase,
    std::string name,
    std::string title,
    unsigned int startingAge
) : attribs(speciesBase.biologicalAttribBias),
    graphics(speciesBase.graphics),
    creatureName(speciesBase._id) {

}

}
