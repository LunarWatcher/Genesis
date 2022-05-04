cmake_minimum_required(VERSION 3.10)
project(Genesis)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
    message( FATAL_ERROR "In-source builds not allowed. Please make a new directory and run CMake from there, or use the -B argument." )
endif()

if (NOT CMAKE_BUILD_TYPE)
    # Prevent explicit flags.
    set(CMAKE_BUILD_TYPE Release)
endif()

set (CMAKE_CXX_STANDARD 20)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure (REQUIRES nlohmann_json/3.10.4 glfw/3.3.5 glew/2.2.0
                        openal/1.21.1 glm/0.9.9.8
                        freetype/2.11.1
                        spdlog/1.10.0
                        GENERATORS cmake)
conan_cmake_autodetect (settings)
conan_cmake_install (PATH_OR_REFERENCE . BUILD missing SETTINGS ${settings})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DAPI_DEBUG")

if (NOT WIN32)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -Wno-c++11-narrowing")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fsanitize=undefined -DGENESIS_DEBUG")
    set (CMAKE_CXX_FLAGS_RELEASE "-O3")

    # Silence the warning for volatile deprecation.
    # Only used to shut the compiler up - glm is out of my control,
    # and is the only source of the warning at this time
    # TODO: find the equivalent for Windoze
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-volatile")

else()
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    # I _think_ CMAKE should be able to figure out windows flags wrt. frameworks
    set (CMAKE_CXX_FLAGS_DEBUG "/Zi")
endif()

add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(run
    COMMAND bin/genesis
    DEPENDS genesis
    COMMENT "Run the game")
add_custom_target(test
    COMMAND bin/tests
    DEPENDS tests
    COMMENT "Test the game")
