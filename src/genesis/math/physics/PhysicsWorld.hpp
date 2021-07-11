#include "PhysicsController.hpp"

#include <map>
#include <memory>

namespace genesis {

class PhysicsWorld {
private:
    /*
     * Contains a map of stages and priorities
     * For the time being, only idx 0 is used, and the future
     * type is more likely to be an enum than an int, but it
     * makes refactoring easier when the time comes.
     */
    std::map<int, std::vector<std::shared_ptr<PhysicsController>>> stageControllerMap;

public:
    void registerControllers(int scene, const std::vector<std::shared_ptr<PhysicsController>>& controllers);

    void tick();
    void clickElement(double x, double y);
};

}
