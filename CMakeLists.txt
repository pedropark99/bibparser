
cmake_minimum_required(VERSION 3.12)
project(bibparser)



add_executable(bibparser
	src/main.cpp
	src/read_bib.cpp
)

target_include_directories(bibparser PRIVATE include)

set_property(TARGET bibparser PROPERTY CXX_STANDARD 20)
message("CXX Standard: ${CXX_STANDARD}")

