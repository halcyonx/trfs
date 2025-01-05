cmake_minimum_required(VERSION 3.22)

include(cmake/trfs_version.cmake)

project(trfs
        VERSION ${TRFS_VER}
        DESCRIPTION "trfs project provides a functionality for game creation"
        LANGUAGES CXX)

add_subdirectory("deps/SDL2")
add_subdirectory("deps/spdlog")
add_subdirectory("deps/json")
add_subdirectory("deps/imgui")
add_subdirectory("deps/stb_image")

if (WIN32)
    add_subdirectory("deps/glad")
    set(LINKED_LIBRARIES SDL2main SDL2-static glad)
    add_definitions(-DPLATFORM_WINDOWS)
elseif (ANDROID)
    set(LINKED_LIBRARIES SDL2 SDL2main GLESv3 EGL)
    add_definitions(-DPLATFORM_ANDROID)
elseif (APPLE)
    add_subdirectory("deps/glad")
    set(LINKED_LIBRARIES SDL2main SDL2-static glad)
    add_definitions(-DPLATFORM_MACOS)
endif()

# Configure version header
configure_file (
    "${PROJECT_SOURCE_DIR}/src/Version.h.in"
    "${PROJECT_BINARY_DIR}/src/Version.h"
)

list(APPEND LINKED_LIBRARIES spdlog stb_image nlohmann_json::nlohmann_json imgui)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_library(trfs "")

target_sources(trfs PRIVATE ${SOURCES})
source_group(Sources FILES ${SOURCES})

target_include_directories(trfs PRIVATE "deps/SDL2/include")
target_include_directories(trfs PUBLIC "deps/glm")
target_include_directories(trfs PRIVATE "deps/spdlog/include")
target_include_directories(trfs PRIVATE "deps/json/include")
target_include_directories(trfs PUBLIC "deps/imgui")
target_include_directories(trfs PRIVATE "deps/stb_image/include")
target_include_directories(trfs PRIVATE "${PROJECT_BINARY_DIR}/src")

if (WIN32 OR APPLE)
    target_include_directories(trfs PRIVATE "deps/glad/include")
endif()

target_include_directories(trfs PUBLIC "src")
target_precompile_headers(trfs PRIVATE "src/Precompiled.h")
target_link_libraries(trfs ${LINKED_LIBRARIES})

if (WIN32 OR APPLE)
    add_subdirectory("deps/googletest")
    add_subdirectory("tests")
endif()
