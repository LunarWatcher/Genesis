
set (SOURCE_FILES genesis/Main.cpp
                    # Rendering
                    genesis/rendering/Model.cpp genesis/rendering/Shader.cpp
                    genesis/rendering/Renderer.cpp
                    genesis/rendering/shaders/DefaultShader.cpp
                    genesis/rendering/shaders/TextShader.cpp
                    # Textures
                    genesis/rendering/Texture.cpp
                    genesis/rendering/atlases/WorldTexture.cpp
                    genesis/rendering/atlases/FontAtlas.cpp
                    # Camera
                    genesis/rendering/view/Camera.cpp
                    # Entities
                    genesis/rendering/Entity.cpp
                    # Environment
                    genesis/rendering/environment/Chunk.cpp
                    # Core
                    genesis/core/WorldController.cpp
                    # Controls
                    genesis/controls/InputManager.cpp
                    # Game
                    genesis/world/EntityController.cpp
                    genesis/world/PlayerCamp.cpp
                    # Math
                    genesis/math/Perlin.cpp
)

add_executable(genesis ${SOURCE_FILES})
target_include_directories(genesis PUBLIC ${CONAN_INCLUDE_DIRS})
target_include_directories(genesis PUBLIC ./)
target_include_directories(genesis PUBLIC ../stb/)

target_link_libraries(genesis ${CONAN_LIBS})

set (resources
    # Shaders {{{
    shaders/default.frag shaders/default.vert
    shaders/text.frag shaders/text.vert
    # }}}
    images/programmer.png
)

foreach(resource IN LISTS resources)
    configure_file(./res/${resource}
        ${CMAKE_BINARY_DIR}/${resource} COPYONLY)
endforeach()
