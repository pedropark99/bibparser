#pragma once
#include <string>
#include <list>

#include "tokenizer.hpp"

class Parser
{
private:
    Tokenizer tokenizer;

public:
    Parser(std::string path_to_bib_file);
    Token get_next_token();
};




