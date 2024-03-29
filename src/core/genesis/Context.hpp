#pragma once

#include "genesis/core/data/DataHelper.hpp"
#include "genesis/core/data/DataLoader.hpp"
#include "genesis/rendering/Renderer.hpp"

#include "genesis/rendering/atlases/FontAtlas.hpp"
#include "genesis/rendering/atlases/TextureAtlas.hpp"
#include "genesis/rendering/impl/Renderer.hpp"
#include "genesis/rendering/shaders/DefaultShader.hpp"
#include "genesis/rendering/shaders/TextShader.hpp"
#include "genesis/rendering/shaders/UIShader.hpp"
#include "genesis/rendering/view/Camera.hpp"

#include <memory>

namespace genesis {

class Context {
private:
    Context();
public:
    std::shared_ptr<Renderer> renderer;
    DataLoader dataLoader;
    // Maybe init this using the dataloader later? Idfk, more refactoring is required
    std::shared_ptr<DataHelper> dataHelper;

    std::shared_ptr<Camera> camera;
    std::shared_ptr<DefaultShader> textureShader;
    std::shared_ptr<TextShader> textShader;
    std::shared_ptr<UIShader> uiShader;
    // TODO: refactor. Going to end up having to stitch together several textures
    // during load. 
    //
    // Might be better to outsource to DataLoader or something? Could also be a
    // sneaky way to create the atlas definitions for tracking IDs and stuff
    std::shared_ptr<TextureAtlas> texturePack;
    std::shared_ptr<FontAtlas> fontAtlas;
    
    void initRendererDeps();

    static Context& getInstance() {
        static Context inst;
        return inst;
    }
};

}
