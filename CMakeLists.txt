
cmake_minimum_required(VERSION 3.12)
project(bibparser)



add_executable(bibparser
	src/main.cpp
	src/read_bib.cpp
	src/tokenizer.cpp
	src/global_variables.cpp
    src/string_utils.cpp
)

target_include_directories(bibparser PRIVATE include)

set_property(TARGET bibparser PROPERTY CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
message("CXX Standard: ${CXX_STANDARD}")



find_package(Catch2 3 REQUIRED)

# These tests can use the Catch2-provided main
add_executable(tests
    tests/tests.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

