#include "WorldTexture.hpp"
#include "genesis/rendering/Constants.hpp"

namespace genesis {

WorldTexture::WorldTexture(const std::string& sourceFile)
        : Texture(sourceFile, 64, 64),
          models{
                  // clang-format off
        {WorldTile::GRASS, std::make_shared<Model>(genesis::Constants::square,
            [&](Model* model) {
                model->bindIndexBuffer(genesis::Constants::squareIndices);
                model->createVBO(1, 2, generateFromPosition(0, 0));
            })}, //
        {WorldTile::STONE, std::make_shared<Model>(genesis::Constants::square,
            [&](Model* model) {
                model->bindIndexBuffer(genesis::Constants::squareIndices);
                model->createVBO(1, 2, generateFromPosition(1, 0));
            })}, //
                                                  // clang-format on
          } {
    //
}

} // namespace genesis
