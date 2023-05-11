add_library(genesis-data STATIC
    genesis/conf/Settings.cpp

    genesis/game/json/SpeciesLoader.cpp
    genesis/game/json/TraitLoader.cpp
)
target_include_directories(genesis-data PUBLIC .)
target_link_libraries(genesis-data PUBLIC genesis-deps)
