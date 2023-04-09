#pragma once

#include "genesis/core/data/DataHelper.hpp"
#include "genesis/core/data/DataLoader.hpp"
#include "genesis/rendering/Renderer.hpp"

namespace genesis {

class Context {
private:
    Context() {}
public:
    Renderer renderer;
    DataLoader dataLoader;
    // Maybe init this using the dataloader later? Idfk, more refactoring is required
    DataHelper dataHelper;

    static Context& getInstance() {
        static Context inst;
        return inst;
    }
};

}
