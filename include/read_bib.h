#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace bibparser
{

    extern std::filesystem::path path_to_example;
    extern std::string bib_file;

    std::string read_bib_file(std::string path);
    std::string remove_white_spaces(std::string bib_file);
    void TraverseString(std::string& str);

}