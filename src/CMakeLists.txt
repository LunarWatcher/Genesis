
set (SOURCE_FILES genesis/Main.cpp
                    # Rendering {{{
                    genesis/rendering/Model.cpp genesis/rendering/Shader.cpp
                    genesis/rendering/Renderer.cpp
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
                    genesis/math/physics/PhysicsController.cpp
                    # }}}
                    # }}}
)

add_executable(genesis ${SOURCE_FILES})
# Executable dependencies {{{
target_include_directories(genesis PUBLIC ${CONAN_INCLUDE_DIRS})
target_include_directories(genesis PUBLIC ./)
target_include_directories(genesis PUBLIC ../stb/)

target_link_libraries(genesis ${CONAN_LIBS})
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
