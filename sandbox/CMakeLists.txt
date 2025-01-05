if (WIN32)
	add_executable(sandbox "")
elseif (ANDROID)
	add_library(sandbox SHARED "")
elseif (APPLE)
	add_executable(sandbox)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp")

target_sources(sandbox PRIVATE ${SOURCES})

target_include_directories(sandbox PRIVATE "src")
target_include_directories(sandbox PRIVATE "../trfs/src")
target_precompile_headers(sandbox REUSE_FROM trfs)
get_target_property(pch_headers sandbox PRECOMPILE_HEADERS_REUSE_FROM)
message("sandbox PRECOMPILE_HEADERS_REUSE_FROM: " ${pch_headers})
target_link_libraries(sandbox trfs)
