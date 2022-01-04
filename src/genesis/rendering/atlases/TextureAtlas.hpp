#pragma once

#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Texture.hpp"

#include <map>

namespace genesis {

struct TextureMetadata {
    /**
     * Refers to the relative offset within the texture atlas.
     */
    int tileId;

    /**
     * Contains the underlying model for the texture.
     */
    std::shared_ptr<Model> model;
};

class TextureAtlas : public Texture {
private:
    int atlasUnits;

    std::map<std::string, TextureMetadata> models;
    std::vector<std::vector<GLfloat>> uvCoordinates;

public:
    TextureAtlas(const std::string& sourceFile);

    std::shared_ptr<Model> getModel(const std::string& type) {
        // map takes care of returning a nullptr if the tile doesn't exist
        // But it shouldn't ever trigger a type that doesn't exist. Fucking bigbrain
        // right there, Olivia :blobthinksmart:
        return models[type].model;
    }

    std::pair<int, int> decodeCoordinates(const std::string& textureID);
    std::pair<int, int> decodeCoordinates(int offset);
};

} // namespace genesis
