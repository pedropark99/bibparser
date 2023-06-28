
cmake_minimum_required(VERSION 3.12)
project(bibparser LANGUAGES CXX)



add_executable(bibparser
	src/main.cpp
	src/read_bib.cpp
	src/tokenizer.cpp
    src/parser.cpp
    src/string_utils.cpp
    src/syntax_checker.cpp
)

target_include_directories(bibparser PRIVATE include)

set_property(TARGET bibparser PROPERTY CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_INIT "-g")

message("CXX Standard: ${CXX_STANDARD}")



find_package(Catch2 3 REQUIRED)

# These tests can use the Catch2-provided main
add_executable(test_bibparser
    tests/tests.cpp
)

target_include_directories(test_bibparser PRIVATE include)
target_link_libraries(test_bibparser PRIVATE Catch2::Catch2WithMain)
