add_library(genesis-data STATIC
    genesis/conf/Settings.cpp

    genesis/game/json/CreatureLoader.cpp
    genesis/game/json/CivilisationLoader.cpp
)
target_include_directories(genesis-data PUBLIC .)
target_link_libraries(genesis-data PUBLIC genesis-deps)
