#pragma once

#include <unordered_map>
#include "ZLayer.hpp"

#include <spdlog/spdlog.h>

namespace genesis {

class MapArea {
private:
    static std::shared_ptr<spdlog::logger> logger;
    std::unordered_map<int, ZLayer*> layers;

    std::vector<Entity*> entities;

    unsigned int width, height;

    void set(ZLayer*);
public:
    MapArea(unsigned int width, unsigned int height);
    ~MapArea();

    void addEntity(Entity* e);

    /**
     * Returns a list of entities.
     *
     * Note that the quadrant attribute is currently unused, but will be added
     * in the future.
     */
    std::vector<Entity*> getEntities(int quadrant);

    friend class WorldGenerator;
};

}
