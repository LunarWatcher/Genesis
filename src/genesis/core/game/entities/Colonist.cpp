#include "Colonist.hpp"

#include "genesis/rendering/Renderer.hpp"

namespace genesis {

Colonist::Colonist(const ColonistGenes& genes, const std::string& colonistName, const glm::vec3& spawnPosition, size_t age, unsigned int hitpoints, unsigned int armor)
        : Entity(
            Renderer::getInstance().getTexturePack()->getTextureMetadata("genesis:colonist_a")
                .model,
            spawnPosition
        ), Inventory(24), colonistName(colonistName),
        age(age), hitpoints(hitpoints),
        armor(armor),
        alive(true), genes(genes) {
    updateTexture();
    textureName = pickTexture();
}

std::string Colonist::pickTexture() {
    switch (genes.s) {
    case Species::RED_FOX:
        // TODO: Rename the textures
        return "genesis:colonist_a";
    case Species::ARCTIC_FOX:
        break;
    case Species::SILVER_FOX:
        break;
    case Species::GREY_WOLF:
        break;
    case Species::ARCTIC_WOLF:
        break;
    }

    return "genesis:colonist_a";
}

void Colonist::updateTexture() {
    std::string newTex = pickTexture();
    if (newTex == textureName) return;
    textureName = newTex;

    model = Renderer::getInstance().getTexturePack()->getTextureMetadata(newTex).model;
}

}
