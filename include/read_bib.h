#pragma once
#include <string>
#include <vector>
#include <filesystem>

namespace bibparser
{
    std::vector<std::string> read_bib_file(std::string path);

    void TraverseString(std::string& str);

    extern std::vector<std::string> bib_file;

}