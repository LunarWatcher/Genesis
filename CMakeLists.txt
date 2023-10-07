cmake_minimum_required(VERSION 3.24)
project(Genesis)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory and run CMake from there, or use the -B argument.")
endif()

if (NOT CMAKE_BUILD_TYPE)
    # Make explicit flags redundant for release builds
    set(CMAKE_BUILD_TYPE Release)
endif()

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Git)
if (EXISTS ${GIT_EXECUTABLE})
    message(STATUS "Checking if Git submodules are initialised...")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive)
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update)
else()
    message(WARNING "GIT_EXECUTABLE isn't saved. Make sure you have Git on your path")
endif()


set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DAPI_DEBUG")

if (NOT WIN32)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wno-c++11-narrowing")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DGENESIS_DEBUG")
    set (CMAKE_CXX_FLAGS_RELEASE "-O3")

    # Silence the warning for volatile deprecation.
    # Only used to shut the compiler up - glm is out of my control,
    # and is the only source of the warning at this time
    # TODO: find the equivalent for Windoze
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-volatile")

    include(CheckCXXSourceCompiles)
    check_cxx_source_compiles("
#include <atomic>
#include <string_view>

int main() {
    std::atomic<std::string_view> x;
    x.store(\"I like trains\");
    x.load();
}
    " HAS_BUILTIN_ATOMIC)
    if (NOT HAS_BUILTIN_ATOMIC)
        set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -latomic")
    endif()
else()
    # As of CMake 3.15, no manual MSVC framework options have to be set
    set (CMAKE_CXX_FLAGS_DEBUG "/Zi")
endif()

set(SPDLOG_FMT_EXTERNAL ON CACHE STRING "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE STRING "" FORCE)
set(ALSOFT_UTILS OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)

set(STB_TAG "5736b15f7ea0ffb08dd38af21067c314d6a3aae9" CACHE STRING "" FORCE)

include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.11.0)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(stc GIT_REPOSITORY https://github.com/LunarWatcher/stc)
FetchContent_MakeAvailable(stc)

FetchContent_Declare(nlohmann
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2)
FetchContent_MakeAvailable(nlohmann)

FetchContent_Declare(stb GIT_REPOSITORY https://github.com/LunarWatcher/stb-cmake)
FetchContent_MakeAvailable(stb)

FetchContent_Declare(openal
    GIT_REPOSITORY https://github.com/kcat/openal-soft
    GIT_TAG 1.23.1)
FetchContent_Declare(_glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.3.8)
FetchContent_Declare(_glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG 47585fde0c49fa77a2bf2fb1d2ead06999fd4b6e)
FetchContent_Declare(_glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
    GIT_TAG 908ac2eb680e920fea65e9986c5200f4b98a089c)

FetchContent_MakeAvailable(_glew)
FetchContent_MakeAvailable(_glfw)
FetchContent_MakeAvailable(_glm)
FetchContent_MakeAvailable(openal)

# Has to be set after OpenAL's declaration to make sure it doesn't inherit -fsanitize, as
# this causes undefined references, because reasons :)
if (NOT WIN32)
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")
endif()

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)

add_custom_target(run
    COMMAND genesis
    DEPENDS genesis
    COMMENT "Run genesis")
add_custom_target(test
    COMMAND tests
    DEPENDS tests
    COMMENT "Test genesis")
