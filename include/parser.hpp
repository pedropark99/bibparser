#pragma once
#include <string>
#include <list>

#include "tokenizer.hpp"

class Parser
{
private:
    std::list<Token> tokens;
public:
    Parser();
    get_next_token();
};




