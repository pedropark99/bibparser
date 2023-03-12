#pragma once
#include <string>

namespace bibparser
{

    std::string read_bib_file(std::string path);

}

std::string get_path_to_file(int argc, char *argv[]);