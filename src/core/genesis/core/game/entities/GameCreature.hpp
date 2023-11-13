#pragma once

#include "genesis/game/Species.hpp"
#include "genesis/rendering/Entity.hpp"

namespace genesis {

// TODO: separate out data fields into a separate struct
class GameCreature : public Entity {
private:
    AttributeInfo attribs;
    /**
     * Contains the details used for rendering.
     */
    GraphicsInfo graphics;

    std::string creatureName;
    std::string name;
    std::string title;

    unsigned int age;

    Gender gender = Gender::NONE;
public:
    GameCreature(
        SpeciesInfo& speciesBase,
        std::string name,
        std::string title,
        unsigned int startingAge
    );

    virtual ~GameCreature() = default;


};

}
