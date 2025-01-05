cmake_minimum_required(VERSION 3.22)

project(stb_image)

include_directories("include/")

set(SOURCE src/stb_image.cpp)

add_library(${PROJECT_NAME} ${SOURCE})

target_link_libraries(stb_image)
