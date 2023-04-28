add_library(genesis-rendering STATIC
    genesis/rendering/Renderer.cpp
    genesis/rendering/Model.cpp
    genesis/rendering/Texture.cpp
    genesis/rendering/Shader.cpp
    genesis/rendering/Entity.cpp
    genesis/rendering/flow/Scene.cpp
    genesis/rendering/gl/Framebuffer.cpp

    genesis/input/InputProcessor.cpp

    # TODO: refactor
    genesis/math/physics/PhysicsController.cpp
    genesis/world/EntityController.cpp

    genesis/meta/Stb.cpp

)
target_include_directories(genesis-rendering PUBLIC .)
target_link_libraries(genesis-rendering PUBLIC genesis-deps genesis-math genesis-data)
