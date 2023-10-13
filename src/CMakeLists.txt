add_executable(genesis core/genesis/Main.cpp)

add_subdirectory(core)
add_subdirectory(data)
add_subdirectory(math)
add_subdirectory(render-engine)

# Meta libraries {{{
add_library(genesis-deps INTERFACE)
target_link_libraries(
    genesis-deps 
INTERFACE 
    stc spdlog::spdlog glm::glm nlohmann_json::nlohmann_json libglew_shared stb::stb
)

# }}}

add_library(genesis-bundle INTERFACE)
target_link_libraries(genesis-bundle INTERFACE genesis-core)

target_link_libraries(genesis genesis-bundle)
