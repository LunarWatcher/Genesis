add_library(genesis-math STATIC
    genesis/math/physics/Rectangle.cpp
)
target_include_directories(genesis-math PUBLIC .)
target_link_libraries(genesis-math PUBLIC genesis-deps)
