#include "WorldTexture.hpp"
#include "genesis/rendering/Constants.hpp"

namespace genesis {
// clang-format off
#define STANDARD_ENTRY(tileType, x, y) { WorldTile::tileType, \
       std::make_shared<Model>(genesis::Constants::square, \
       [&](Model* model) { \
           model->bindIndexBuffer(genesis::Constants::squareIndices); \
           model->createVBO(1, 2, generateFromPosition(x, y)); \
       }) \
     }
// clang-format on

WorldTexture::WorldTexture(const std::string& sourceFile)
        : Texture(sourceFile, 64, 64),
          models{
              // clang-format off
              STANDARD_ENTRY(GRASS, 0, 0),
              STANDARD_ENTRY(STONE, 1, 0),
              STANDARD_ENTRY(COLONIST_A, 0, 12)
              // clang-format on
          } {}

} // namespace genesis
