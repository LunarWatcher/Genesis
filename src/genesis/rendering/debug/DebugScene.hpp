#pragma once

#include "genesis/math/physics/Rectangle.hpp"
#include "genesis/rendering/flow/Scene.hpp"
#include "genesis/rendering/objects/Primitive.hpp"

namespace genesis {

class DebugScene : public Scene {
public:

    std::vector<std::shared_ptr<Primitive>> orthoPrims;
    std::vector<std::shared_ptr<Primitive>> perspectivePrims;

    void render() override;
    void tick() override {}

    void clear() {
        orthoPrims.clear();
        perspectivePrims.clear();
    }

    void debugRect(const std::shared_ptr<Rectangle>& collider);

};

}
