#include "genesis/rendering/flow/Scene.hpp"

namespace genesis {

class SplashScene : public Scene {
public:

    void render() override;
    void tick()   override;

    void onDestroy() override;

};

}
