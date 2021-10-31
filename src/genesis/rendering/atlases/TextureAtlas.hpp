#pragma once

#include "genesis/rendering/Model.hpp"
#include "genesis/rendering/Texture.hpp"

#include <map>

namespace genesis {

enum class WorldTile {
    // Ground {{{
    GRASS = 0, //
    STONE = 1, //
    // }}}
    // Entities {{{
    COLONIST_A = 12 * 16,
    // }}}
};

class TextureAtlas : public Texture {
private:
    int atlasUnits;

    std::map<WorldTile, std::shared_ptr<Model>> models;
    std::vector<std::vector<GLfloat>> uvCoordinates;

    std::pair<int, int> decodeCoordinates(int offset);
public:
    TextureAtlas(const std::string& sourceFile);

    std::shared_ptr<Model> getModel(WorldTile type) {
        // map takes care of returning a nullptr if the tile doesn't exist
        // But it shouldn't ever trigger a type that doesn't exist. Fucking bigbrain
        // right there, Olivia :blobthinksmart:
        return models[type];
    }
};

} // namespace genesis
