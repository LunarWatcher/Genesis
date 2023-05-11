#include "GameCreature.hpp"
#include "genesis/Context.hpp"

namespace genesis {


GameCreature::GameCreature(
    SpeciesInfo& speciesBase,
    std::string name,
    std::string title,
    unsigned int startingAge
    // TODO: this model init only accounts for isStatic == true, which isn't a guarantee later:tm:
) : Entity(Context::getInstance().texturePack->getTextureMetadata(speciesBase.graphics.source).model, glm::vec3{}), 
    attribs(speciesBase.biologicalAttribBias),
    graphics(speciesBase.graphics),
    creatureName(name),
    title(title),
    age(startingAge) {

}

}
