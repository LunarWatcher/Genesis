#include "MapArea.hpp"

namespace genesis {

MapArea::MapArea(unsigned int width, unsigned int height) : width(width), height(height) {
    logger->debug("Map initialised: {} x {}", this->width, this->height);
}

MapArea::~MapArea() {
    for (auto& [_, layer] : layers) {
        delete layer;
    }
}

void MapArea::set(ZLayer* layer) {
    if (layer == nullptr) {
        logger->error("Received nullptr layer");
        throw std::runtime_error("Cannot have a null layer");
    }

    if (layers.contains(layer->zLevel)) {
        logger->warn("Overwriting layer at {}", layer->zLevel);
    }

    layers[layer->zLevel] = layer;
}

void MapArea::addEntity(Entity* e) {
    entities.push_back(e);
}

std::vector<Entity*> MapArea::getEntities(int) {
    return entities;
}

}
