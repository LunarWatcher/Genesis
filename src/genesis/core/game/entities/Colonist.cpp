#include "Colonist.hpp"

#include "genesis/rendering/Renderer.hpp"

namespace genesis {

Colonist::Colonist(const std::string& textureName, const std::string& colonistName, const glm::vec3& spawnPosition, size_t age)
        : Entity(
            Renderer::getInstance().getTexturePack()->getTextureMetadata(textureName)
                .model,
            spawnPosition
        ), textureName(textureName), colonistName(colonistName), age(age),
        alive(true) {
}

}
