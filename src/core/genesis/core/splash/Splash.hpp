#include "genesis/rendering/flow/Scene.hpp"
#include "genesis/rendering/ui/Text.hpp"

namespace genesis {

class SplashScene : public Scene {
private:
    TextEntity text;
public:

    SplashScene();

    void render() override;
    void tick()   override;


};

}
