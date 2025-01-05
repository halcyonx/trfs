cmake_minimum_required(VERSION 3.22)

include(cmake/project_version.cmake)

project(breakout VERSION ${BREAKOUT_VER}
        DESCRIPTION "Breakout game"
        LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS YES)

add_subdirectory("trfs")
add_subdirectory("breakout")
add_subdirectory("sandbox")

set_target_properties(trfs PROPERTIES FOLDER "trfs")
set_target_properties(breakout PROPERTIES FOLDER "Game")
set_target_properties(sandbox PROPERTIES FOLDER "Sandbox")
