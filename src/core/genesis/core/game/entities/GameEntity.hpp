#pragma once

#include "genesis/game/Creature.hpp"
#include "genesis/rendering/Entity.hpp"

namespace genesis {

class GameEntity : public Entity {
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
    // TODO: set up gender config on a species level in the files
    // The initial setup is going to just be static, but could probably set up
    // a probability function. Like,
    // "genders": {
    //     "male": {
    //         "probability": 0.485
    //     },
    //     "female": {
    //         "probability". 0.505
    //     },
    //     "trans_fem": {
    //         "probability": 0.004
    //     },
    //     "trans_masc": {
    //         "probability": 0.004
    //     },
    //     ...
    // }
    //
    // Could probably use that as the way to define body differences, if any. Future me problem though;
    // ignoring gender for now for the sake of making something playable.
    //
    // Though not really sure if I'll bother in the end. We'll see. A DF-level of simulation will
    // take years to do anyway, and I imagine I'll rather spend time on stuff differentiating the
    // game from DF.
    //
    // The goal isn't a true clone anyway. The core mechanics are just heavily inspired by it
    Gender gender = Gender::NONE;

public:
    GameEntity(CreatureInfo& speciesBase);


};

}
