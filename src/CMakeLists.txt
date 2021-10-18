
set (SOURCE_FILES
    # Rendering {{{
    genesis/rendering/Model.cpp genesis/rendering/Shader.cpp
    genesis/rendering/Renderer.cpp
    # }}}
    # Scenes {{{
    genesis/core/menu/Menu.cpp
    # }}}
    # Shaders {{{
    genesis/rendering/shaders/DefaultShader.cpp
    genesis/rendering/shaders/TextShader.cpp
    genesis/rendering/shaders/ParticleShader.cpp
    # }}}
    # Textures {{{
    genesis/rendering/Texture.cpp
    genesis/rendering/atlases/WorldTexture.cpp
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
    # Entities  {{{
    genesis/rendering/Entity.cpp
    # }}}
    # Environment {{{
    genesis/rendering/environment/Chunk.cpp
    # }}}
    # Core {{{
    genesis/core/WorldController.cpp
    genesis/conf/Settings.cpp
    # }}}
    # Controls {{{
    genesis/controls/InputManager.cpp
    # }}}
    # Game {{{
    genesis/world/EntityController.cpp
    genesis/world/PlayerCamp.cpp
    # }}}
    # Math {{{
    genesis/math/Perlin.cpp
    # Physics {{{
    genesis/math/physics/Rectangle.cpp
    genesis/math/physics/PhysicsWorld.cpp
    genesis/math/physics/PhysicsController.cpp
    # }}}
    # }}}
    # Logging {{{
    genesis/logging/Loggers.cpp
    # }}}
)

add_library(genesissrc STATIC ${SOURCE_FILES})
add_executable(genesis genesis/Main.cpp)

# Executable dependencies {{{
target_include_directories(genesissrc PUBLIC ${CONAN_INCLUDE_DIRS})
target_include_directories(genesissrc PUBLIC ./)
target_include_directories(genesissrc PUBLIC ../stb/ ../stc/src)

target_link_libraries(genesissrc ${CONAN_LIBS})
# }}}
# Resource copying {{{
set (resources
    # Shaders {{{
    shaders/default.frag shaders/default.vert
    shaders/text.frag shaders/text.vert
    shaders/particle.frag shaders/particle.vert
    # }}}
    images/programmer.png
)

foreach(resource IN LISTS resources)
    configure_file(./res/${resource}
        ${CMAKE_BINARY_DIR}/${resource} COPYONLY)
endforeach()
# }}}

target_link_libraries(genesis genesissrc)
