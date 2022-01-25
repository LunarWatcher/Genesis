#pragma once

#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Texture.hpp"

#include <map>

namespace genesis {

struct TextureMetadata {
    /**
     * Refers to the relative offset within the texture atlas.
     *
     * Not sure if we need to keep this in the long run.
     */
    int tileId;

    std::vector<GLfloat> uvCoordinates;

    /**
     * Contains the underlying model for the texture.
     */
    std::shared_ptr<Model> model;
};

class TextureAtlas : public Texture {
private:
    int atlasUnits;

    std::map<std::string, TextureMetadata> models;

public:
    TextureAtlas(const std::string& sourceFile);

    const TextureMetadata& getTextureMetadata(const std::string& type) {
        // map takes care of returning a nullptr if the tile doesn't exist
        // But it shouldn't ever trigger a type that doesn't exist. Fucking bigbrain
        // right there, Olivia :blobthinksmart:
        return models[type];
    }
};

} // namespace genesis
