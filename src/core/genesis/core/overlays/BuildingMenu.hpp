#pragma once

#include "genesis/rendering/flow/Scene.hpp"

namespace genesis {

class BuildingMenu : public Scene {
public:
    BuildingMenu();

    void render() override;
};

}
