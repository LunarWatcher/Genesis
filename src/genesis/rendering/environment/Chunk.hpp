#pragma once

#include "genesis/core/WorldController.hpp"
#include "genesis/rendering/Entity.hpp"
#include <GL/gl.h>
#include <memory>
#include <string>
#include <vector>

namespace genesis {

class Chunk : public Renderable {
public:
    static inline constexpr int CHUNK_SIZE = 16;

private:
    std::vector<std::vector<std::shared_ptr<Entity>>> chunkMap;
    int chunkX, chunkY;

public:
    Chunk(WorldController& runner, int chunkX, int chunkY);
    void render(DefaultShader& shader);
};

} // namespace genesis
