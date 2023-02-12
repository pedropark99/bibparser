#pragma once
#include <string>
#include <filesystem>

namespace bibparser
{

    extern std::filesystem::path path_to_example;
    extern std::string bib_file;

    std::string read_bib_file(std::string path);

}