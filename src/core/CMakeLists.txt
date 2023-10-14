set (SOURCE_FILES
    # Core {{{
    genesis/Context.cpp
    genesis/rendering/impl/Renderer.cpp
    # }}}
    # Scenes {{{
    genesis/core/menu/Menu.cpp
    genesis/core/splash/Splash.cpp
    # }}}
    # Shaders {{{
    genesis/rendering/shaders/DefaultShader.cpp
    genesis/rendering/shaders/TextShader.cpp
    genesis/rendering/shaders/UIShader.cpp
    # }}}
    # Textures {{{
    genesis/rendering/atlases/TextureAtlas.cpp
    genesis/rendering/atlases/FontAtlas.cpp
    # }}}
    # Data {{{
    genesis/core/data/DataLoader.cpp
    # }}}

    # UI {{{

    genesis/rendering/ui/Text.cpp
    # }}}
    # Camera {{{
    genesis/rendering/view/Camera.cpp
    # }}}

    # Environment {{{
    genesis/core/game/chunks/ZLayer.cpp
    genesis/core/game/chunks/MapArea.cpp
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
    # Game {{{
    # Entities {{{
    genesis/core/game/entities/GameCreature.cpp
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
    genesis/rendering/objects/Primitive.cpp
    genesis/math/physics/Ray.cpp
    # }}}
    # }}}
    # Logging {{{
    genesis/logging/Loggers.cpp
    # }}}
    # TODO: place sanely
    genesis/core/game/chunks/MapLayers.cpp
    # AI {{{
    genesis/core/game/ai/MapAI.cpp
    # }}}
)

add_library(genesis-core STATIC ${SOURCE_FILES})
target_link_libraries(genesis-core PUBLIC genesis-deps
    genesis-rendering
    genesis-math
    genesis-data
)

# Executable dependencies {{{
target_include_directories(genesis-core PUBLIC ./)
target_include_directories(genesis-core PUBLIC ../stb/)

# }}}
# Resource copying {{{
set (resources_old
    # Shaders {{{
    shaders/default.frag shaders/default.vert
    shaders/text.frag shaders/text.vert
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
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/data

    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/res/fonts ${CMAKE_BINARY_DIR}/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/res/images ${CMAKE_BINARY_DIR}/images
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/res/shaders ${CMAKE_BINARY_DIR}/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
    COMMENT "Copying resources"
)


# }}}

add_dependencies(genesis-core resources)
