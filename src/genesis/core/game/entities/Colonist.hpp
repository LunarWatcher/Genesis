#pragma once

#include "genesis/rendering/Entity.hpp"

namespace genesis {

class Colonist : public Entity {
public:
    // Variables {{{
    // Internal management {{{
    std::string textureName;
    // }}}

    // Colonist attributes {{{
    std::string colonistName;
    size_t age;

    bool alive;
    // }}}
    // }}}
    Colonist(const std::string& textureName, const std::string& colonistName, const glm::vec3& spawnPosition, size_t age);


};

}
