add_executable(genesis core/genesis/Main.cpp)

add_subdirectory(core)
add_subdirectory(render-engine)

# Meta libraries {{{
add_library(genesis-deps INTERFACE)
target_link_libraries(genesis-deps INTERFACE stc ${CONAN_LIBS})
target_include_directories(genesis-deps INTERFACE ${CMAKE_SOURCE_DIR}/stb/)

# }}}

add_library(genesis-bundle INTERFACE)
target_link_libraries(genesis-bundle INTERFACE genesis-core)

target_link_libraries(genesis genesis-bundle)
