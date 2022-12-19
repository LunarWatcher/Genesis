#include "Colonist.hpp"

#include "genesis/rendering/Renderer.hpp"

namespace genesis {

Colonist::Colonist(const std::string& textureName, const std::string& colonistName, const glm::vec3& spawnPosition, size_t age, unsigned int hitpoints, unsigned int armor)
        : Entity(
            Renderer::getInstance().getTexturePack()->getTextureMetadata(textureName)
                .model,
            spawnPosition
        ), Inventory(24), textureName(textureName), colonistName(colonistName),
        age(age), hitpoints(hitpoints),
        armor(armor),
        alive(true) {
}

}
