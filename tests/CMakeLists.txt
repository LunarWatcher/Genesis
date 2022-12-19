add_executable(tests src/TestRunner.cpp
    src/SettingsTest.cpp
    src/DateTests.cpp
)

# Catch2 {{{
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.2.0
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(tests Catch2::Catch2)
# }}}

target_link_libraries(tests genesissrc)
