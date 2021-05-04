#pragma once

#include "genesis/rendering/Entity.hpp"

#include <GL/gl.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace genesis {

typedef std::map<int, std::vector<std::vector<std::shared_ptr<Entity>>>> ChunkMap;

class Chunk : public Renderable {
public:
    static inline constexpr int CHUNK_SIZE = 16;

private:
    ChunkMap chunkMap;
    int chunkX, chunkY;

public:
    Chunk(int chunkX, int chunkY);
    void render();

    auto getX() {
        return chunkX;
    }
    auto getY() {
        return chunkY;
    }
};

} // namespace genesis
