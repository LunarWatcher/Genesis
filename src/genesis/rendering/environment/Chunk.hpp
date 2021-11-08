#pragma once

#include "genesis/rendering/Entity.hpp"

#include <GL/gl.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace genesis {

// Typedefs for the underlying map {{{
// TODO: this cannot be optimal. There _has_ to be a better way to do this.
// Probably mixing in some chunked rendering? Could let us pass a list of IDs instead
// Y'know what, that's fucking brilliant.
// We only need one model anyway. The chunk's chunkMap is intended to only consist of
// the "blocks" (I say blocks, it's not properly 3D to justify that)
typedef std::vector<std::vector<int>> FlatMap;
typedef std::map<int, FlatMap> ChunkMap;
// }}}

class Chunk : public Entity {
public:
    static constexpr int CHUNK_SIZE = 16;

private:
    ChunkMap chunkMap;
    int chunkX, chunkY;

    void regenerateVertices();

public:
    Chunk(int chunkX, int chunkY);

    void render();

    //void erase(int x, int y, int z = 0);
    //std::shared_ptr<Entity> get(int x, int y, int z = 0);
    //void set(int tile, int x, int y, int z = 0);

    auto getX() {
        return chunkX;
    }
    auto getY() {
        return chunkY;
    }
};

} // namespace genesis
