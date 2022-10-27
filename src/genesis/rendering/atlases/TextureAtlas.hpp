#pragma once

#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Texture.hpp"

#include <map>

namespace genesis {

struct TextureMetadata {
    /**
     * Refers to the relative offset within the texture atlas.
     *
     * Primarily intended for future use as an identifier within the atlas.
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
    std::map<int, std::string> tileIDToString;

public:
    TextureAtlas(const std::string& sourceFile);

    const TextureMetadata& getTextureMetadata(const std::string& type) {
        // Dear past me,
        // fuck you.
        // This shit's a reference, not a pointer. Must've been valid at one point, but
        // not anymore.
        // Hostile regards,
        // future you
        // ---
        // map takes care of returning a nullptr if the tile doesn't exist
        // But it shouldn't ever trigger a type that doesn't exist. Fucking bigbrain
        // right there, Olivia :blobthinksmart:
        //return models[type];
        return models.at(type);
    }
};

} // namespace genesis
