#pragma once

#include "genesis/core/game/chunks/Tile.hpp"
#include "genesis/rendering/Entity.hpp"

// God damn apple
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

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
typedef std::vector<std::vector<std::shared_ptr<Tile>>> FlatMap;
typedef std::map<int, FlatMap> ChunkMap;
// }}}

class Chunk : public Entity {
private:
    ChunkMap chunkMap;
    int chunkX, chunkY;
    int lastTileLevel = -9999;

    void regenerateVertices();
    bool dirty = false;

public:
    Chunk(int chunkX, int chunkY);

    void render();

    //void erase(int x, int y, int z = 0);
    //std::shared_ptr<Entity> get(int x, int y, int z = 0);
    void set(std::shared_ptr<Tile> tile, int x, int z, int y = 0);
    
    /**
     * Gets the top y for a given tile within the chunk.
     *
     * Note: requires chunk-relative coords
     */
    int getTopY(int x, int y);

    auto getX() {
        return chunkX;
    }
    auto getY() {
        return chunkY;
    }
    friend class WorldGenerator;
};

} // namespace genesis
