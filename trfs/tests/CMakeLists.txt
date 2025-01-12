set(target_name "trfs_tests")

add_executable(${target_name} "")

set(SOURCES
        "src/TestMain.cpp"
        "src/TestFileReader.cpp"
        "src/TestLayerStack.cpp"
        "src/TestFileBuffer.cpp"
)

target_sources(${target_name} PRIVATE ${SOURCES})

target_include_directories(${target_name} PRIVATE " src")
target_include_directories(${target_name} PRIVATE "../deps/SDL/include")
target_include_directories(${target_name} PRIVATE "../deps/googletest/include")
target_include_directories(${target_name} PRIVATE "../src")
target_precompile_headers(${target_name} REUSE_FROM trfs)

get_target_property(pch_headers ${target_name} PRECOMPILE_HEADERS_REUSE_FROM)
message("${target_name} PRECOMPILE_HEADERS_REUSE_FROM: " ${pch_headers})
target_compile_definitions(${target_name} PRIVATE TESTS_ENABLED=1)
target_link_libraries(${target_name} trfs gtest gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${target_name})
