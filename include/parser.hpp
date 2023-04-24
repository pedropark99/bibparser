#pragma once
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>

#include "tokenizer.hpp"


enum ParserState {
    PARSING = 421,
    PARSE_ERROR = 422
};


class Parser
{
private:
    Tokenizer tokenizer;
    ParserState parser_state;
    std::unordered_map< TokenType, std::unordered_set<TokenType> >
        expects_next;
    std::list<Token> stack_of_tokens;

public:
    Parser(std::string path_to_bib_file);
    void parse_token(Token token);
    void parse_file();
};




