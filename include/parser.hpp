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
    void parse_token(Token token);
    void parse_file();
};




