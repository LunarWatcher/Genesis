set (SOURCE_FILES
    # Rendering {{{
    genesis/rendering/Renderer.cpp
    # }}}
    # Scenes {{{
    genesis/core/menu/Menu.cpp
    genesis/rendering/debug/DebugScene.cpp
    # }}}
    # Shaders {{{
    genesis/rendering/shaders/DefaultShader.cpp
    genesis/rendering/shaders/TextShader.cpp
    genesis/rendering/shaders/ParticleShader.cpp
    # }}}
    # Textures {{{
    genesis/rendering/atlases/TextureAtlas.cpp
    genesis/rendering/atlases/FontAtlas.cpp
    # }}}
    # Effects {{{
    genesis/rendering/particles/ParticleEmitter.cpp
    # }}}
    # UI {{{

    genesis/rendering/ui/Text.cpp
    # }}}
    # Camera {{{
    genesis/rendering/view/Camera.cpp
    # }}}

    # Environment {{{
    genesis/rendering/environment/Chunk.cpp
    genesis/core/game/chunks/Tile.cpp

    genesis/core/game/chunks/TileGenerator.cpp
    genesis/core/game/chunks/tilegen/TerrainTileGenerator.cpp
    genesis/core/game/chunks/tilegen/ContainerTileGenerator.cpp

    genesis/core/game/chunks/tiles/ContainerTile.cpp
    # }}}
    # Core {{{
    genesis/core/game/World.cpp

    genesis/core/data/DataHelper.cpp
    genesis/core/game/generation/RNGesus.cpp

    # }}}
    # Controls {{{
    genesis/controls/InputController.cpp
    # }}}
    # Game {{{
    genesis/world/EntityController.cpp
    genesis/world/PlayerCamp.cpp
    # Entities {{{
    genesis/core/game/entities/Colonist.cpp
    # }}}
    # World generation {{{
    genesis/core/game/generation/WorldGenerator.cpp
    # }}}
    # Object types {{{
    genesis/core/game/items/Inventory.cpp
    # }}}
    # Objects {{{
    genesis/core/game/objects/Caravan.cpp
    # }}}
    # }}}
    # Math {{{
    genesis/math/Perlin.cpp
    # Physics {{{
    genesis/math/physics/Rectangle.cpp
    genesis/rendering/objects/Primitive.cpp
    genesis/math/physics/PhysicsController.cpp

    genesis/math/physics/Ray.cpp
    # }}}
    # }}}
    # Logging {{{
    genesis/logging/Loggers.cpp
    # }}}

    # Meta {{{
    genesis/meta/Stb.cpp
    # }}}
)

add_library(genesis-core STATIC ${SOURCE_FILES})
target_link_libraries(genesis-core PUBLIC genesis-deps
    genesis-rendering
    genesis-math
    genesis-data
)

# Executable dependencies {{{
target_include_directories(genesis-core PUBLIC ${CONAN_INCLUDE_DIRS})
target_include_directories(genesis-core PUBLIC ./)
target_include_directories(genesis-core PUBLIC ../stb/)

# }}}
# Resource copying {{{
set (resources
    # Shaders {{{
    shaders/default.frag shaders/default.vert
    shaders/text.frag shaders/text.vert
    shaders/particle.frag shaders/particle.vert
    shaders/primitive.frag shaders/primitive.vert
    # }}}
    images/programmer.png

    fonts/gamepixies.fnt
    fonts/gamepixies_0.png
)

add_custom_target(resources
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/fonts
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/images
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/res/fonts ${CMAKE_BINARY_DIR}/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/res/images ${CMAKE_BINARY_DIR}/images
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/res/shaders ${CMAKE_BINARY_DIR}/shaders
    COMMENT "Copying resources"
)


# }}}

add_dependencies(genesis-core resources)
