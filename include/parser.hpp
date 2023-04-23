#pragma once
#include <string>
#include <list>
#include <unordered_set>

#include "tokenizer.hpp"

class Parser
{
private:
    Tokenizer tokenizer;
    std::unordered_map< TokenType, std::unordered_set<TokenType> >
        expects_next;
    std::list<Token> stack_of_tokens;

public:
    Parser(std::string path_to_bib_file);
    void parse_token(Token token);
    void parse_file();
};




