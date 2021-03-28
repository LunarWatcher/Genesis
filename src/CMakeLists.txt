
set (SOURCE_FILES genesis/Main.cpp
                    # Rendering
                    genesis/rendering/Model.cpp genesis/rendering/Shader.cpp
                    genesis/rendering/Renderer.cpp genesis/rendering/shaders/DefaultShader.cpp
                    # Textures
                    genesis/rendering/Texture.cpp
                    # Camera
                    genesis/rendering/view/Camera.cpp
                    # Entities
                    genesis/rendering/Entity.cpp
                    # Core
                    genesis/core/Runner.cpp
                    )

add_executable(genesis ${SOURCE_FILES})
target_include_directories(genesis PUBLIC ${CONAN_INCLUDE_DIRS})
target_include_directories(genesis PUBLIC ./)
target_include_directories(genesis PUBLIC ../stb/)

target_link_libraries(genesis ${CONAN_LIBS})

set (resources shaders/default.frag shaders/default.vert "images/test.png")

foreach(resource IN LISTS resources) 
    configure_file(./res/${resource}
        ${CMAKE_BINARY_DIR}/${resource} COPYONLY)
endforeach()
