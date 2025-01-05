if (WIN32)
	add_executable(breakout "")
elseif (ANDROID)
	add_library(breakout SHARED "")
elseif (APPLE)
	add_executable(breakout MACOSX_BUNDLE "")
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

target_sources(breakout PRIVATE ${SOURCES})

target_include_directories(breakout PRIVATE "src")
target_include_directories(breakout PRIVATE "../trfs/src")
target_precompile_headers(breakout REUSE_FROM trfs)
get_target_property(pch_headers breakout PRECOMPILE_HEADERS_REUSE_FROM)
message("breakout PRECOMPILE_HEADERS_REUSE_FROM: " ${pch_headers})
target_link_libraries(breakout trfs)
