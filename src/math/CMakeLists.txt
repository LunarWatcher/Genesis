add_library(genesis-math INTERFACE

)
target_include_directories(genesis-math INTERFACE .)
target_link_libraries(genesis-math INTERFACE genesis-deps)
