#pragma once

namespace genesis {

class World;
class CreatureController;
class AIEngine {
private:
    void simulateColony(CreatureController& cc, World& world);
public:
    void tick(CreatureController& cc, World& world);
};

}
