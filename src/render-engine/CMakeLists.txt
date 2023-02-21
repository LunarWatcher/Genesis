add_library(genesis-rendering STATIC
    genesis/rendering/Model.cpp
    genesis/rendering/Texture.cpp
    genesis/rendering/Shader.cpp
    genesis/rendering/Entity.cpp
)
target_include_directories(genesis-rendering PUBLIC .)
target_link_libraries(genesis-rendering PUBLIC genesis-deps genesis-math genesis-data)
