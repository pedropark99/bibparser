#pragma once
#include <unordered_set>
#include <string>
#include <filesystem>

namespace bibparser{
    extern std::filesystem::path path_to_example;
    extern std::string bib_file;
}

extern const std::unordered_set<char> LETTERS;
extern const std::unordered_set<char> NUMBERS;
extern const std::unordered_set<char> LINES;

